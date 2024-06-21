// ADR; syntax is current-addr(/off in buffer), target-addr(/off)
TEST(0x10000000, de64_ADR(DA_GP(0), 0, 0));
TEST(0x30000000, de64_ADR(DA_GP(0), 0, 1));
TEST(0x70ffffe0, de64_ADR(DA_GP(0), 0, -1));
TEST(0x10000020, de64_ADR(DA_GP(0), 0, 4));
TEST(0x10000020, de64_ADR(DA_GP(0), 0x123456, 0x12345a));
TEST(0x10ffffe0, de64_ADR(DA_GP(0), 0, -4));
TEST(0x107fffe0, de64_ADR(DA_GP(0), 0, 0xffffc));
TEST(0x10800020, de64_ADR(DA_GP(0), 0, -0xffffc));
TEST(0x707fffe0, de64_ADR(DA_GP(0), 0, 0xfffff));
TEST(0x30800000, de64_ADR(DA_GP(0), 0, -0xfffff));
TEST(0x10800000, de64_ADR(DA_GP(0), 0, -0x100000));
TEST(0, de64_ADR(DA_GP(0), 0, 0x100000));
TEST(0, de64_ADR(DA_GP(0), 0, 0x100001));
TEST(0, de64_ADR(DA_GP(0), 0, -0x100001));

// ADRP; syntax is current-addr, target-addr. Due to ADRPs sematnics, the offset
// within the page must be fixed, so an offset into an arbitrarily aligned
// buffer will not work. Example:
{
  intptr_t codeaddr = 0x4324242c;   // Address where ADRP will be placed
  intptr_t tgt = codeaddr + 0x2f3a; // Target address x0 should point to
  TEST(0xf0000000, de64_ADRP(DA_GP(0), codeaddr, tgt));
  TEST(0x910d9800, de64_ADDxi(DA_GP(0), DA_GP(0), tgt & 0xfff));
}
TEST(0x90000000, de64_ADRP(DA_GP(0), 0x0000, 0x0001));
TEST(0x90000000, de64_ADRP(DA_GP(0), 0x0000, 0x0fff));
TEST(0xb0000000, de64_ADRP(DA_GP(0), 0x0000, 0x1000));
TEST(0xb0000000, de64_ADRP(DA_GP(0), 0x0fff, 0x1000));
TEST(0xb0000000, de64_ADRP(DA_GP(0), 0x0fff, 0x1fff));
TEST(0x90000000, de64_ADRP(DA_GP(0), 0x1000, 0x1fff));
TEST(0x90800000, de64_ADRP(DA_GP(0), 0x100000000, 0));
TEST(0xd07fffe0, de64_ADRP(DA_GP(0), 0x100000000, 0x1ffffe000));
TEST(0xf0ffffe0, de64_ADRP(DA_GP(0), 0x100000000, 0xfffff000));
TEST(0xd0ffffe0, de64_ADRP(DA_GP(0), 0x100000000, 0xffffe000));
TEST(0xf07fffe0, de64_ADRP(DA_GP(0), 0, 0xffffffff));
TEST(0, de64_ADRP(DA_GP(0), 0, 0x100000000));
