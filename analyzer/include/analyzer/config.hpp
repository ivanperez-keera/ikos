/*******************************************************************************
 *
 * Configuration file to set up the numerical abstract domain used by
 * analyses.
 *
 * Author: Jorge A. Navas
 *
 * Contributors: Maxime Arthaud
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

#ifndef ANALYZER_CONFIG_HPP
#define ANALYZER_CONFIG_HPP

#include <ikos/domains/intervals.hpp>
#include <ikos/domains/congruences.hpp>
#include <ikos/domains/intervals_congruences.hpp>
#include <ikos/domains/octagons.hpp>
#include <ikos/domains/var_packing_dbm.hpp>
#include <ikos/domains/var_packing_dbm_congruences.hpp>

#include <analyzer/analysis/common.hpp>

namespace analyzer {

typedef ikos::z_number number_t;

/*
 *  The invariants computed by the analyses will be using the type
 *  abs_num_domain_t which is based on the types number_t and varname_t.
 *
 *  If we use function summarization, the function summaries will be using
 *  the type sum_abs_num_domain_t, also based on types number_t and varname_t.
 */

#if defined(INTERVAL_DOMAIN)
typedef ikos::interval_domain< number_t, varname_t > abs_num_domain_t;
typedef ikos::var_packing_dbm< number_t, varname_t > sum_abs_num_domain_t;
#elif defined(CONGRUENCE_DOMAIN)
typedef ikos::congruence_domain< number_t, varname_t > abs_num_domain_t;
typedef ikos::var_packing_dbm_congruence< number_t, varname_t >
    sum_abs_num_domain_t;
#elif defined(INTERVAL_CONGRUENCE_DOMAIN)
typedef ikos::interval_congruence_domain< number_t, varname_t >
    abs_num_domain_t;
typedef ikos::var_packing_dbm_congruence< number_t, varname_t >
    sum_abs_num_domain_t;
#elif defined(OCTAGON_DOMAIN)
typedef ikos::octagon< number_t, varname_t > abs_num_domain_t;
typedef ikos::octagon< number_t, varname_t > sum_abs_num_domain_t;
#elif defined(DBM_DOMAIN)
typedef ikos::dbm< number_t, varname_t > abs_num_domain_t;
typedef ikos::dbm< number_t, varname_t > sum_abs_num_domain_t;
#elif defined(VAR_PACKING_DBM_DOMAIN)
typedef ikos::var_packing_dbm< number_t, varname_t > abs_num_domain_t;
typedef ikos::var_packing_dbm< number_t, varname_t > sum_abs_num_domain_t;
#else // default
typedef ikos::interval_domain< number_t, varname_t > abs_num_domain_t;
typedef ikos::var_packing_dbm< number_t, varname_t > sum_abs_num_domain_t;
#endif

} // end namespace analyzer

#endif // ANALYZER_CONFIG_HPP
