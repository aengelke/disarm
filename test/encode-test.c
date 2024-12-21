
#include <disarm64.h>
#include <inttypes.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool test_MOVconst(void) {
  static const struct {
    uint64_t cnst;
    uint32_t enc[4];
  } cases[] = {
      {0x0000000000000000, {0xd2800000}}, // MOVZx
      {0xffffffffffffffff, {0x92800000}}, // MOVNx
      {0x0000000000000001, {0xd2800020}}, // MOVZx
      {0xfffffffffffffffe, {0x92800020}}, // MOVNx
      {0x0000000000001234, {0xd2824680}}, // MOVZx
      {0xffffffffffffedcb, {0x92824680}}, // MOVNx
      {0x000000000000ffff, {0xd29fffe0}}, // MOVZx
      {0xffffffffffff0000, {0x929fffe0}}, // MOVNx
      {0x0000000000010000, {0xd2a00020}}, // MOVZx16
      {0xfffffffffffeffff, {0x92a00020}}, // MOVNx16
      {0x0000000012340000, {0xd2a24680}}, // MOVZx16
      {0xffffffffedcbffff, {0x92a24680}}, // MOVNx16
      {0x00000000ffff0000, {0xd2bfffe0}}, // MOVZx16
      {0xffffffff0000ffff, {0x92bfffe0}}, // MOVNx16
      {0x000000000001ffff, {0xb24043e0}}, // ORR
      {0xfffffffffffe0000, {0xb26fbbe0}}, // ORR
      {0x000000000002ffff, {0x12bfffa0}}, // MOVNw16
      // XXX: could use MOVN+MOVK
      {0xfffffffffffd0000, {0xd2bfffa0, 0xf2dfffe0, 0xf2ffffe0}},
      {0x000000001234ffff, {0x12bdb960}}, // MOVNw16
      {0x00000000ffff0001, {0x129fffc0}}, // MOVNw
      {0x00000000ffff1234, {0x129db960}}, // MOVNw
      {0x1122334455667788, {0xd28ef100, 0xf2aaacc0, 0xf2c66880, 0xf2e22440}},
      {0x0000334455667788, {0xd28ef100, 0xf2aaacc0, 0xf2c66880}},
      {0x1122000055667788, {0xd28ef100, 0xf2aaacc0, 0xf2e22440}},
      {0x1122334400007788, {0xd28ef100, 0xf2c66880, 0xf2e22440}},
      {0x1122334455660000, {0xd2aaacc0, 0xf2c66880, 0xf2e22440}},
      {0x1122334400000000, {0xd2c66880, 0xf2e22440}},
      {0x1122000055660000, {0xd2aaacc0, 0xf2e22440}},
  };
  bool failed = false;
  for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
    const uint32_t* exp = cases[i].enc;
    unsigned exp_cnt = !exp[1] ? 1 : !exp[2] ? 2 : !exp[3] ? 3 : 4;

    uint32_t buf[4] = {0};
    unsigned cnt = de64_MOVconst(buf, DA_GP(0), cases[i].cnst);
    if (cnt != exp_cnt || memcmp(buf, exp, sizeof(buf)) != 0) {
      failed = true;
      printf("err MOVconst %d{%x,%x,%x,%x} %d{%x,%x,%x,%x} %016" PRIx64 "\n",
             exp_cnt, exp[0], exp[1], exp[2], exp[3], cnt, buf[0], buf[1],
             buf[2], buf[3], cases[i].cnst);
    }
  }
  return failed;
}

static bool test(uint32_t exp, uint32_t encoded, const char* name) {
  if (exp == encoded)
    return false;
  printf("err %08x %08x (%s)\n", exp, encoded, name);
  return true;
}
#define TEST(exp, encoded) failed |= test(exp, encoded, #encoded)

int main(void) {
  bool failed = false;

  failed |= test_MOVconst();

#include "encode-test-adcsbc.inc"
#include "encode-test-addsub-imm.inc"
#include "encode-test-addsub-shift.inc"
#include "encode-test-adr.inc"
#include "encode-test-bfm-extr.inc"
#include "encode-test-branchreg.inc"
#include "encode-test-fcma.inc"
#include "encode-test-hint.inc"
#include "encode-test-immfmov.inc"
#include "encode-test-immlogical.inc"
#include "encode-test-immsimd.inc"
#include "encode-test-mem.inc"
#include "encode-test-memfp.inc"
#include "encode-test-memsimd.inc"
#include "encode-test-pauth.inc"
#include "encode-test-simd-shr-vec-imm.inc"
#include "encode-test-simdcopy.inc"
#include "encode-test-simdxelem.inc"
#include "encode-test-sys.inc"

  // Unsorted tests
  TEST(0x9b020c20, de64_MADDx(DA_GP(0), DA_GP(1), DA_GP(2), DA_GP(3)));
  TEST(0x9b027c20, de64_MADDx(DA_GP(0), DA_GP(1), DA_GP(2), DA_ZR));
  TEST(0x9b027c20, de64_MULx(DA_GP(0), DA_GP(1), DA_GP(2)));
  TEST(0x9b028c20, de64_MSUBx(DA_GP(0), DA_GP(1), DA_GP(2), DA_GP(3)));
  TEST(0x9b02fc20, de64_MSUBx(DA_GP(0), DA_GP(1), DA_GP(2), DA_ZR));
  TEST(0x9b02fc20, de64_MNEGx(DA_GP(0), DA_GP(1), DA_GP(2)));
  TEST(0xfa41300f, de64_CCMPx(DA_GP(0), DA_GP(1), 0xf, DA_LO));
  TEST(0, de64_CCMPx(DA_GP(0), DA_GP(1), 0x10, DA_LO));
  TEST(0, de64_CCMPx(DA_GP(0), DA_GP(1), -1, DA_LO));
  TEST(0x9a823020, de64_CSELx(DA_GP(0), DA_GP(1), DA_GP(2), DA_CC));
  TEST(0x9a823420, de64_CSINCx(DA_GP(0), DA_GP(1), DA_GP(2), DA_CC));
  TEST(0xda823020, de64_CSINVx(DA_GP(0), DA_GP(1), DA_GP(2), DA_CC));
  TEST(0xda823420, de64_CSNEGx(DA_GP(0), DA_GP(1), DA_GP(2), DA_CC));
  TEST(0x9a813020, de64_CSELx(DA_GP(0), DA_GP(1), DA_GP(1), DA_CC));
  TEST(0x9a813420, de64_CSINCx(DA_GP(0), DA_GP(1), DA_GP(1), DA_CC));
  TEST(0x9a813420, de64_CINCx(DA_GP(0), DA_GP(1), DA_CS));
  TEST(0xda813020, de64_CSINVx(DA_GP(0), DA_GP(1), DA_GP(1), DA_CC));
  TEST(0xda813020, de64_CINVx(DA_GP(0), DA_GP(1), DA_CS));
  TEST(0xda813420, de64_CSNEGx(DA_GP(0), DA_GP(1), DA_GP(1), DA_CC));
  TEST(0xda813420, de64_CNEGx(DA_GP(0), DA_GP(1), DA_CS));
  TEST(0x9a9f33e0, de64_CSELx(DA_GP(0), DA_ZR, DA_ZR, DA_CC));
  TEST(0x9a9f37e0, de64_CSINCx(DA_GP(0), DA_ZR, DA_ZR, DA_CC));
  TEST(0x9a9f37e0, de64_CSETx(DA_GP(0), DA_CS));
  TEST(0xda9f33e0, de64_CSINVx(DA_GP(0), DA_ZR, DA_ZR, DA_CC));
  TEST(0xda9f33e0, de64_CSETMx(DA_GP(0), DA_CS));
  TEST(0xda9f37e0, de64_CSNEGx(DA_GP(0), DA_ZR, DA_ZR, DA_CC));
  TEST(0xda9f37e0, de64_CNEGx(DA_GP(0), DA_ZR, DA_CS));

  // SIMD logical
  TEST(0x0ea11c20, de64_MOV8b(DA_V(0), DA_V(1)));
  TEST(0x4ea11c20, de64_MOV16b(DA_V(0), DA_V(1)));

  TEST(0x0f08a420, de64_SXTL_8h(DA_V(0), DA_V(1)));
  TEST(0x0f10a420, de64_SXTL_4s(DA_V(0), DA_V(1)));
  TEST(0x0f20a420, de64_SXTL_2d(DA_V(0), DA_V(1)));
  TEST(0x4f08a420, de64_SXTL2_8h(DA_V(0), DA_V(1)));
  TEST(0x4f10a420, de64_SXTL2_4s(DA_V(0), DA_V(1)));
  TEST(0x4f20a420, de64_SXTL2_2d(DA_V(0), DA_V(1)));

#if DA64_HAVE_LSE
  TEST(0x08207c1e, de64_CASPw(DA_GP(0), DA_GP(30), DA_GP(0)));
  TEST(0, de64_CASPw(DA_GP(1), DA_GP(30), DA_GP(0)));
  TEST(0, de64_CASPw(DA_GP(0), DA_GP(29), DA_GP(0)));
#endif

  puts(failed ? "Some tests FAILED" : "All tests PASSED");
  return failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
