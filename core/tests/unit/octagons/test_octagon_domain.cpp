#include <iostream>

#include <ikos/algorithms/linear_constraints.hpp>
#include <ikos/common/bignums.hpp>
#include <ikos/common/types.hpp>
#include <ikos/domains/intervals.hpp>
#include <ikos/domains/octagons.hpp>

using namespace std;
using namespace ikos;

typedef string_factory::indexed_string varname_t;
typedef variable< z_number, varname_t > z_var;
typedef linear_constraint< z_number, varname_t > linear_constraint_t;
typedef linear_expression< z_number, varname_t > linear_expression_t;
typedef octagon< z_number, varname_t > octagon_domain_t;
typedef interval< z_number > interval_t;
typedef interval_domain< z_number, varname_t > interval_domain_t;

int main(int argc, char** argv) {
  string_factory vfac;

  try {
    varname_t x(vfac["x"]);
    varname_t y(vfac["y"]);
    varname_t z(vfac["z"]);
    varname_t w(vfac["w"]);

    octagon_domain_t inv(octagon_domain_t::top());
    cout << inv << endl;

    inv.assign(x, 0);
    linear_constraint_t c3(z_var(w) == z_var(x));
    inv += c3;
    inv.apply(OP_ADDITION, x, x, 1);
    linear_constraint_t c1(z_var(x) == z_var(y));
    linear_constraint_t c2(z_var(x) <= z_var(z));
    inv += c1;
    inv += c2;

    cout << inv << endl;
  } catch (ikos_error& e) {
    cout << e;
  }
  cout << "---------------------------" << endl;

  try {
    varname_t v_0 = vfac["\"0\""];
    varname_t v_i = vfac["i"];
    varname_t v_i1 = vfac["\"i+\""];
    varname_t v_n = vfac["n"];

    octagon_domain_t inv;
    inv += linear_constraint_t(z_var(v_0) == 0);
    inv += linear_constraint_t(z_var(v_i) >= z_var(v_0));
    inv += linear_constraint_t(z_var(v_n) == 11);
    inv += linear_constraint_t(z_var(v_n) >= z_var(v_0) + 1);
    inv += linear_constraint_t(z_var(v_i) <= z_var(v_n) - 1);
    inv += linear_constraint_t(z_var(v_i1) == z_var(v_i) + 1);

    // interval_domain_t itv = inv.to_intervals() ;
    cout << inv << endl;
  } catch (ikos_error& e) {
    cout << e;
  }
  cout << "---------------------------" << endl;

  try {
    varname_t v0 = vfac["\"0\""];
    varname_t vi = vfac["i"];
    varname_t vn = vfac["n"];
    varname_t vi_old = vfac["i_old"];

    octagon_domain_t inv;
    inv += linear_constraint_t(z_var(v0) == 0);
    inv += linear_constraint_t(z_var(vn) == 10);
    inv += linear_constraint_t(z_var(vi) >= z_var(v0));
    inv += linear_constraint_t(z_var(vi) <= z_var(vn) - 1);
    inv.assign(vi_old, z_var(vi));
    cout << inv << endl;

    // Some tests
    octagon_domain_t tmp1(inv);
    tmp1 += linear_constraint_t(z_var(vi) <= -1);
    if (tmp1.is_bottom()) {
      cout << vi << " < " << v0 << " is false." << endl;
    } else {
      cout << vi << " < " << v0 << " is true." << endl;
    }

    octagon_domain_t tmp2(inv);
    tmp2 += linear_constraint_t(z_var(vi_old) <= -1);
    if (tmp2.is_bottom()) {
      cout << vi_old << " < " << v0 << " is false." << endl;
    } else {
      cout << vi_old << " < " << v0 << " is true." << endl;
    }
  } catch (ikos_error& e) {
    cout << e;
  }
  cout << "---------------------------" << endl;

  try {
    // GOOD
    varname_t vi = vfac["i"];
    varname_t vn = vfac["n"];
    ///////////////////////////////////////////////////////
    octagon_domain_t inv1;
    // inv1 += linear_constraint_t( z_var(vn) >= 1); // <----------
    inv1.assign(vi, 0);
    inv1 += linear_constraint_t(z_var(vi) <= z_var(vn) - 1);
    inv1.apply(OP_ADDITION, vi, vi, 1);
    cout << "inv1:" << inv1 << endl;
    ///////////////////////////////////////////////////////
    octagon_domain_t inv2(inv1);
    // inv2 += linear_constraint_t( z_var(vn) >= 1);
    inv2 += linear_constraint_t(z_var(vi) <= z_var(vn) - 1);
    inv2.apply(OP_ADDITION, vi, vi, 1);
    cout << "inv2:" << inv2 << endl;
    ///////////////////////////////////////////////////////
    octagon_domain_t inv3(inv1 | inv2);
    cout << "join inv1 and inv2:" << inv3 << endl;
    inv3 += linear_constraint_t(z_var(vi) <= z_var(vn) - 1);
    cout << "inv3:" << inv3 << endl;
  } catch (ikos_error& e) {
    cout << e;
  }
  cout << "---------------------------" << endl;

  try {
    // BAD
    varname_t vi = vfac["i"];
    varname_t vn = vfac["n"];
    ///////////////////////////////////////////////////////
    octagon_domain_t inv1;
    inv1 += linear_constraint_t(z_var(vn) >= 1);
    inv1.assign(vi, 0);
    inv1 += linear_constraint_t(z_var(vi) <= z_var(vn) - 1);
    inv1.apply(OP_ADDITION, vi, vi, 1);
    cout << "inv1:" << inv1 << endl;
    ///////////////////////////////////////////////////////
    octagon_domain_t inv2(inv1);
    // inv2 += linear_constraint_t( z_var(vn) >= 1);
    inv2 += linear_constraint_t(z_var(vi) <= z_var(vn) - 1);
    inv2.apply(OP_ADDITION, vi, vi, 1);
    cout << "inv2:" << inv2 << endl;
    ///////////////////////////////////////////////////////
    octagon_domain_t inv3(inv1 | inv2);
    cout << "join inv1 and inv2:" << inv3 << endl;
    inv3 += linear_constraint_t(z_var(vi) <= z_var(vn) - 1);
    cout << "inv3:" << inv3 << endl;
  } catch (ikos_error& e) {
    cout << e;
  }
  cout << "---------------------------" << endl;

  try {
    // downsizing
    varname_t vi = vfac["i"];
    varname_t vn = vfac["n"];
    varname_t tmp1 = vfac["tmp1"];
    varname_t tmp2 = vfac["tmp2"];
    varname_t tmp3 = vfac["tmp3"];
    octagon_domain_t inv1;
    inv1 += linear_constraint_t(z_var(vn) >= 1);
    inv1.assign(vi, 0);
    inv1 += linear_constraint_t(z_var(vi) <= z_var(vn) - 1);
    inv1.apply(OP_ADDITION, vi, vi, 1);
    inv1.apply(OP_ADDITION, tmp1, vi, 2);
    inv1.apply(OP_ADDITION, tmp2, tmp1, 2);
    inv1.apply(OP_ADDITION, tmp3, tmp2, 4);
    cout << "inv1:" << inv1 << endl;

    inv1 -= vi;
    cout << "after removing " << vi << ":" << inv1 << endl;
    inv1 -= vn;
    cout << "after removing " << vn << ":" << inv1 << endl;
    inv1 -= tmp3;
    cout << "after removing " << tmp3 << ":" << inv1 << endl;
    inv1 -= tmp1;
    cout << "after removing " << tmp1 << ":" << inv1 << endl;
  } catch (ikos_error& e) {
    cout << e;
  }
  cout << "---------------------------" << endl;

  try {
    varname_t vj = vfac["j"];
    varname_t vj1 = vfac["j1"];
    octagon_domain_t inv;

    inv += linear_constraint_t(z_var(vj) >= 0);
    inv += linear_constraint_t(z_var(vj) <= 10);
    inv += linear_constraint_t(z_var(vj1) >= 1);
    inv += linear_constraint_t(z_var(vj1) <= 11);
    inv += linear_constraint_t(z_var(vj1) == z_var(vj) + 1);
    inv += linear_constraint_t(z_var(vj) <= 9);
    // interval_t itv = inv[vj1];
    cout << inv << endl;
    // cout << "j1=" << itv << endl;
  } catch (ikos_error& e) {
    cout << e;
  }
  cout << "---------------------------" << endl;

  try {
    varname_t x(vfac["x"]);
    varname_t y(vfac["y"]);

    octagon_domain_t s1(octagon_domain_t::top());

    s1.assign(x, 0);
    s1.assign(y, 0);

    cout << "Loc 1: " << s1 << endl;
    octagon_domain_t s2(s1);
    s2.apply(OP_ADDITION, x, x, 1);
    cout << "Loc 2a (after x++): " << s2 << endl;
    s2.apply(OP_ADDITION, y, y, 1);
    cout << "Loc 2b (after y++): " << s2 << endl;

    octagon_domain_t s3 = s1 | s2;

    cout << "Loc 3, after join: " << s3 << endl;

    octagon_domain_t s4(s3);
    s4.apply(OP_ADDITION, x, x, 1);

    cout << "Loc 4a (after x++): " << s4 << endl;

    s4.apply(OP_ADDITION, y, y, 1);

    cout << "Loc 4b (after y++): " << s4 << endl;

    octagon_domain_t s5 = s4 || s3;

    cout << "Loc 5, after widening : " << s5 << endl;
  } catch (ikos_error& e) {
    cout << e;
  }
  cout << "---------------------------" << endl;

  try {
    varname_t x(vfac["x"]);
    varname_t y(vfac["y"]);
    varname_t n(vfac["n"]);
    varname_t tmp_x(vfac["tmp_x"]);
    varname_t tmp_y(vfac["tmp_y"]);

    ////
    octagon_domain_t s1(octagon_domain_t::top());
    s1.assign(x, 0);
    s1.assign(y, 0);
    cout << "Loc 1: " << s1 << endl;
    ////
    octagon_domain_t s2(s1);
    s2 += linear_constraint_t(z_var(x) <= z_var(n));
    cout << "Loc 2: " << s2 << endl;

    octagon_domain_t s3(s2);
    s3.apply(OP_ADDITION, tmp_x, x, 1);
    s3.apply(OP_ADDITION, tmp_y, y, 1);
    s3.assign(x, z_var(tmp_x));
    s3.assign(y, z_var(tmp_y));
    cout << "Loc 3 tmp_x:=x+1, tmp_y:=y+1, x:=tmp_x, y:=tmp_y= " << s3 << endl;

    octagon_domain_t s4 = s1 | s3;
    cout << "Loc 4: Loc 1 U Loc 3=" << s4 << endl;

    octagon_domain_t s5(s4);
    s5 += linear_constraint_t(z_var(x) <= z_var(n));
    cout << "Loc 2': x<=n " << s5 << endl;

    octagon_domain_t s6(s5);
    s6.apply(OP_ADDITION, tmp_x, x, 1);
    s6.apply(OP_ADDITION, tmp_y, y, 1);
    s6.assign(x, z_var(tmp_x));
    s6.assign(y, z_var(tmp_y));
    cout << "Loc 3': tmp_x:=x+1, tmp_y:=y+1, x:=tmp_x, y:=tmp_y= " << s6
         << endl;

    octagon_domain_t s7 = s1 | s6;
    cout << "Loc 4': Loc 1 U Loc 3'=" << s7 << endl;

    octagon_domain_t s8 = s4 || s7;

    cout << "Loc 4': Widening(Loc 4, Loc 4')=" << s8 << endl;

    octagon_domain_t s9(s8);
    s9 += linear_constraint_t(z_var(x) <= z_var(n));
    cout << "Loc 2'': x<=n " << s9 << endl;

    octagon_domain_t s10(s9);
    s10.apply(OP_ADDITION, tmp_x, x, 1);
    s10.apply(OP_ADDITION, tmp_y, y, 1);
    s10.assign(x, z_var(tmp_x));
    s10.assign(y, z_var(tmp_y));
    cout << "Loc 3'': tmp_x:=x+1, tmp_y:=y+1, x:=tmp_x, y:=tmp_y= " << s10
         << endl;

    octagon_domain_t s11 = s1 | s10;
    cout << "Loc 4'': Loc 1 U Loc 3''=" << s11 << endl;

    octagon_domain_t s12 = s8 || s11;

    cout << "Loc 4'': Widening(Loc 4', Loc 4'')=" << s12 << endl;
  } catch (ikos_error& e) {
    cout << e;
  }
  cout << "---------------------------" << endl;

  return 1;
}
