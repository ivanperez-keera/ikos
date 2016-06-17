/*******************************************************************************
 *
 * ARBOS pass for regression test cfg-trans-llvm-phi-3
 *
 * Authors: Nija Shi
 *
 * Contact: ikos@lists.nasa.gov
 *
 * Notices:
 *
 * Copyright (c) 2011-2016 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Disclaimers:
 *
 * No Warranty: THE SUBJECT SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY OF
 * ANY KIND, EITHER EXPRESSED, IMPLIED, OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL CONFORM TO SPECIFICATIONS,
 * ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 * OR FREEDOM FROM INFRINGEMENT, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL BE
 * ERROR FREE, OR ANY WARRANTY THAT DOCUMENTATION, IF PROVIDED, WILL CONFORM TO
 * THE SUBJECT SOFTWARE. THIS AGREEMENT DOES NOT, IN ANY MANNER, CONSTITUTE AN
 * ENDORSEMENT BY GOVERNMENT AGENCY OR ANY PRIOR RECIPIENT OF ANY RESULTS,
 * RESULTING DESIGNS, HARDWARE, SOFTWARE PRODUCTS OR ANY OTHER APPLICATIONS
 * RESULTING FROM USE OF THE SUBJECT SOFTWARE.  FURTHER, GOVERNMENT AGENCY
 * DISCLAIMS ALL WARRANTIES AND LIABILITIES REGARDING THIRD-PARTY SOFTWARE,
 * IF PRESENT IN THE ORIGINAL SOFTWARE, AND DISTRIBUTES IT "AS IS."
 *
 * Waiver and Indemnity:  RECIPIENT AGREES TO WAIVE ANY AND ALL CLAIMS AGAINST
 * THE UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS, AS WELL
 * AS ANY PRIOR RECIPIENT.  IF RECIPIENT'S USE OF THE SUBJECT SOFTWARE RESULTS
 * IN ANY LIABILITIES, DEMANDS, DAMAGES, EXPENSES OR LOSSES ARISING FROM SUCH
 * USE, INCLUDING ANY DAMAGES FROM PRODUCTS BASED ON, OR RESULTING FROM,
 * RECIPIENT'S USE OF THE SUBJECT SOFTWARE, RECIPIENT SHALL INDEMNIFY AND HOLD
 * HARMLESS THE UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS,
 * AS WELL AS ANY PRIOR RECIPIENT, TO THE EXTENT PERMITTED BY LAW.
 * RECIPIENT'S SOLE REMEDY FOR ANY SUCH MATTER SHALL BE THE IMMEDIATE,
 * UNILATERAL TERMINATION OF THIS AGREEMENT.
 *
 ******************************************************************************/

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

#include <arbos/common/common.hpp>
#include <arbos/semantics/ar.hpp>

using namespace arbos;

namespace {

class verifier_error : public error {
private:
  verifier_error();

public:
  verifier_error(std::string msg) : error(msg) {}
  virtual ~verifier_error() {}
}; // class verifer_error

class Verifier : public Visitor {
private:
  std::vector< index64_t > _visited;

private:
  bool isVisited(index64_t uid) {
    return find(_visited.begin(), _visited.end(), uid) != _visited.end();
  }

public:
  Verifier() {}
  virtual void nodeStart(AR_Function&);
  void print(std::ostream& out) { out << "Test passed!" << std::endl; }
};

class VisitorPass : public Pass {
public:
  VisitorPass()
      : Pass("unittest-cfg-trans-llvm-phi-3",
             "Verifier pass for unittest-cfg-trans-llvm-phi-3"){};

  virtual ~VisitorPass() {}

  virtual void execute(AR_Node_Ref< AR_Bundle > bundle) {
    std::cout << "This pass verifies regression test parsing/call-args"
              << std::endl
              << std::endl;
    std::shared_ptr< Verifier > v(new Verifier());
    (*bundle).accept(v);
    v->print(std::cout);
  }
};

// Visitor method implementation

void Verifier::nodeStart(AR_Function& f) {
  if (f.getFunctionId() != "foo")
    return;

  std::string trans =
      "($trans\
  ($edge ($*_if.end_split_1_icmp_false) ($*out_if.end_merge_1_icmp))\
  ($edge ($*_if.end_split_1_icmp_true) ($*out_if.end_merge_1_icmp))\
  ($edge ($*_if.end_split_icmp_false) ($*out_if.end_merge_icmp))\
  ($edge ($*_if.end_split_icmp_true) ($*out_if.end_merge_icmp))\
  ($edge ($*in_entry_to_if.end_phi) ($if.end))\
  ($edge ($*in_if.then_to_if.end_phi) ($if.end))\
  ($edge ($*out_entry_to_if.end_icmp_false) ($*in_entry_to_if.end_phi))\
  ($edge ($*out_entry_to_if.then_icmp_true) ($if.then))\
  ($edge ($*out_if.end_merge_icmp) ($*_if.end_split_1_icmp_true))\
  ($edge ($*out_if.end_merge_icmp) ($*_if.end_split_1_icmp_false))\
  ($edge ($entry) ($*out_entry_to_if.then_icmp_true))\
  ($edge ($entry) ($*out_entry_to_if.end_icmp_false))\
  ($edge ($if.end) ($*_if.end_split_icmp_true))\
  ($edge ($if.end) ($*_if.end_split_icmp_false))\
  ($edge ($if.then) ($*in_if.then_to_if.end_phi))\
  )";

  std::istringstream iss(trans);
  s_expression_istream seis(iss);
  s_expression_ref e;
  seis >> e;

  AR_Node_Ref< AR_Code > body = f.getFunctionBody();
  std::vector< AR_Node_Ref< AR_Basic_Block > > bblocks = (*body).getBlocks();
  assert(bblocks.size() == 13);

  std::pair< bblock_iterator, bblock_iterator > next_bblocks;

  if (e) {
    s_expression expr = *e;
    if (s_pattern("trans") ^ expr) {
      for (std::size_t i = 1; i <= expr.n_args(); i++) {
        s_expression edge = expr[i];
        s_expression_ref src, dest;
        if (s_pattern("edge", src, dest) ^ edge) {
          std::string src_bbname = (static_cast< string_atom& >(**src)).data();
          std::string dest_bbname =
              (static_cast< string_atom& >(**dest)).data();
          AR_Node_Ref< AR_Basic_Block > src_bb =
              (*body).getBasicBlockByNameId(src_bbname);
          next_bblocks = (*src_bb).getNextBlocks();
          bool found = false;
          for (bblock_iterator b = next_bblocks.first; b != next_bblocks.second;
               b++) {
            if ((**b).getNameId() == dest_bbname) {
              found = true;
              break;
            }
          }
          assert(found);
        }
      }
    }
  }
}
}

extern "C" Pass* init() {
  VisitorPass* pass = new VisitorPass();
  return pass;
}
