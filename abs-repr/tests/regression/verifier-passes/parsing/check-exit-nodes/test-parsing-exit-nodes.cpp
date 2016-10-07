/*******************************************************************************
 *
 * ARBOS pass for verifiying exit nodes in an AR function.
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

#include <iostream>

#include <arbos/semantics/ar.hpp>

using namespace arbos;

namespace {

static Option< std::vector< std::string > > list("list,L",
                                                 "Function name and names of "
                                                 "the exit nodes in this "
                                                 "sequence: function, return, "
                                                 "unreachable, ehresume.");

class CheckExitNodesPass : public Pass {
public:
  CheckExitNodesPass()
      : Pass("check-exit-nodes", "Verifies exit nodes in an AR function.") {}
  virtual ~CheckExitNodesPass() {}

  virtual void execute(AR_Node_Ref< AR_Bundle > bundle) {
    assert(list);
    const std::vector< std::string >& v = list;
    assert(v.size() == 4);
    AR_Node_Ref< AR_Function > f = (*(*bundle).getFunctionByNameId(v[0]));
    AR_Node_Ref< AR_Code > c = (*f).getFunctionBody();

    AR_Node_Ref< AR_Basic_Block > exit_bb = (*c).getExitBlock();
    AR_Node_Ref< AR_Basic_Block > unreachable_bb = (*c).getUnreachableBlock();
    AR_Node_Ref< AR_Basic_Block > ehresume_bb = (*c).getEHResumeBlock();

    if (exit_bb.getUID() == 0)
      assert(v[1] == "null");
    else
      assert(v[1] == "*" || v[1] == (*exit_bb).getNameId());

    if (unreachable_bb.getUID() == 0)
      assert(v[2] == "null");
    else
      assert(v[2] == "*" || v[2] == (*unreachable_bb).getNameId());

    if (ehresume_bb.getUID() == 0)
      assert(v[3] == "null");
    else
      assert(v[3] == "*" || v[3] == (*ehresume_bb).getNameId());

    std::cout << "Test passed!" << std::endl;
  }
};
}

extern "C" Pass* init() {
  return new CheckExitNodesPass();
}
