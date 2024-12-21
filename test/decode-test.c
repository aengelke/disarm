
#include <disarm64.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  const struct {
    uint32_t inst;
    unsigned mnem;
    const char* disable_str;
    const char* mnem_str;
    const char* fmt;
  } cases[] = {
#define TESTF(cond, inst, mnem, fmt) {inst, mnem, cond ? 0 : #cond, #mnem, fmt},
#define TEST(...) TESTF(1, __VA_ARGS__)

      // clang-format off
    TEST(0x00000000, DA64I_UDF, "udf #0x0")
    TEST(0x1a000000, DA64I_ADC, "adc w0, w0, w0")
    TEST(0x1a1f03ff, DA64I_ADC, "adc wzr, wzr, wzr")
    TEST(0x9a000000, DA64I_ADC, "adc x0, x0, x0")
    TEST(0x9a1f03ff, DA64I_ADC, "adc xzr, xzr, xzr")
    TEST(0x3a000000, DA64I_ADCS, "adcs w0, w0, w0")
    TEST(0x3a1f03ff, DA64I_ADCS, "adcs wzr, wzr, wzr")
    TEST(0xba000000, DA64I_ADCS, "adcs x0, x0, x0")
    TEST(0xba1f03ff, DA64I_ADCS, "adcs xzr, xzr, xzr")
    TEST(0x5a000000, DA64I_SBC, "sbc w0, w0, w0")
    TEST(0x5a1f03ff, DA64I_SBC, "sbc wzr, wzr, wzr")
    TEST(0xda000000, DA64I_SBC, "sbc x0, x0, x0")
    TEST(0xda1f03ff, DA64I_SBC, "sbc xzr, xzr, xzr")
    TEST(0x7a000000, DA64I_SBCS, "sbcs w0, w0, w0")
    TEST(0x7a1f03ff, DA64I_SBCS, "sbcs wzr, wzr, wzr")
    TEST(0xfa000000, DA64I_SBCS, "sbcs x0, x0, x0")
    TEST(0xfa1f03ff, DA64I_SBCS, "sbcs xzr, xzr, xzr")
    TEST(0x0b204000, DA64I_ADD_EXT, "add w0, w0, w0, uxtw #0")
    TEST(0x0b204c00, DA64I_ADD_EXT, "add w0, w0, w0, uxtw #3")
    TEST(0x0b205000, DA64I_ADD_EXT, "add w0, w0, w0, uxtw #4")
    TEST(0x0b205400, DA64I_UNKNOWN, "")
    TEST(0x0b206000, DA64I_ADD_EXT, "add w0, w0, w0, uxtx #0")
    TEST(0x8b206000, DA64I_ADD_EXT, "add x0, x0, x0, uxtx #0")
    TEST(0x8b2063ff, DA64I_ADD_EXT, "add sp, sp, x0, uxtx #0")
    TEST(0x8b20e000, DA64I_ADD_EXT, "add x0, x0, x0, sxtx #0")
    TEST(0x8b3fe000, DA64I_ADD_EXT, "add x0, x0, xzr, sxtx #0")
    TEST(0x8b204000, DA64I_ADD_EXT, "add x0, x0, w0, uxtw #0")
    TEST(0xd4400000, DA64I_HLT, "hlt #0x0")
    TEST(0x1e23c020, DA64I_FCVT, "fcvt h0, s1")
    TEST(0x10800000, DA64I_ADR, "adr x0, #0xfffffffffff00000")
    TEST(0x28200000, DA64I_STNPW, "stnp w0, w0, [x0, #-0x100]")
    TEST(0xd800001f, DA64I_PRFM_LIT, "prfm #31, #0x0")
    TEST(0x3ca0f800, DA64I_STR_REG_FP, "str q0, [x0, x0, sxtx #4]")
    TESTF(DA64_HAVE_CSSC, 0x5ac01800, DA64I_CTZ, "ctz w0, w0")
    TESTF(DA64_HAVE_CSSC, 0x5ac01c00, DA64I_CNT, "cnt w0, w0")
    TESTF(DA64_HAVE_LSE, 0x08207c1e, DA64I_CASP, "cas w0, w1, w30, wzr, [x0]")
    TESTF(DA64_HAVE_LSE, 0x08207c1f, DA64I_UNKNOWN, "") // Rt must be even
    TESTF(DA64_HAVE_LSE, 0x08217c1e, DA64I_UNKNOWN, "") // Rs must be even
    TESTF(DA64_HAVE_BF16, 0x1e634020, DA64I_BFCVT, "bfcvt h0, s1")
  // clang-format on

#include "decode-test-branchreg.inc"
#include "decode-test-fmovimm.inc"
#include "decode-test-immlogical.inc"
#include "decode-test-immsimd.inc"
#include "decode-test-pauth.inc"
  };

  char buf[128];
  struct Da64Inst res;

  bool failed = false;
  for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
    da64_decode(cases[i].inst, &res);
    da64_format(&res, buf);

    if (cases[i].disable_str) {
      if (res.mnem != DA64I_UNKNOWN || buf[0] != '\0') {
        failed = true;
        printf("err %08x %s (%s) (!%s)\n", cases[i].inst, cases[i].fmt,
               cases[i].mnem_str, cases[i].disable_str);
      }
    } else if (res.mnem != cases[i].mnem || strcmp(buf, cases[i].fmt) != 0) {
      failed = true;
      printf("err %08x %s (%s)\n", cases[i].inst, cases[i].fmt,
             cases[i].mnem_str);
      printf("  mnem: got=%#x expected=%#x (%s)\n", res.mnem, cases[i].mnem,
             cases[i].mnem_str);
      printf("  fmt: got=%s expected=%s\n", buf, cases[i].fmt);
    }
  }

  puts(failed ? "Some tests FAILED" : "All tests PASSED");
  return failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
