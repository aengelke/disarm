#if DA64_HAVE_FCMA
TEST(0x2f421020, de64_FCMLA4h_elem(DA_V(0), DA_V(1), DA_V(2), 0, 0));
TEST(0x2f423020, de64_FCMLA4h_elem(DA_V(0), DA_V(1), DA_V(2), 0, 90));
TEST(0x2f425020, de64_FCMLA4h_elem(DA_V(0), DA_V(1), DA_V(2), 0, 180));
TEST(0x2f427020, de64_FCMLA4h_elem(DA_V(0), DA_V(1), DA_V(2), 0, 270));
TEST(0x2f621020, de64_FCMLA4h_elem(DA_V(0), DA_V(1), DA_V(2), 1, 0));
TEST(0x2f623020, de64_FCMLA4h_elem(DA_V(0), DA_V(1), DA_V(2), 1, 90));
TEST(0x2f625020, de64_FCMLA4h_elem(DA_V(0), DA_V(1), DA_V(2), 1, 180));
TEST(0x2f627020, de64_FCMLA4h_elem(DA_V(0), DA_V(1), DA_V(2), 1, 270));
TEST(0x6f421020, de64_FCMLA8h_elem(DA_V(0), DA_V(1), DA_V(2), 0, 0));
TEST(0x6f423020, de64_FCMLA8h_elem(DA_V(0), DA_V(1), DA_V(2), 0, 90));
TEST(0x6f425020, de64_FCMLA8h_elem(DA_V(0), DA_V(1), DA_V(2), 0, 180));
TEST(0x6f427020, de64_FCMLA8h_elem(DA_V(0), DA_V(1), DA_V(2), 0, 270));
TEST(0x6f621020, de64_FCMLA8h_elem(DA_V(0), DA_V(1), DA_V(2), 1, 0));
TEST(0x6f623020, de64_FCMLA8h_elem(DA_V(0), DA_V(1), DA_V(2), 1, 90));
TEST(0x6f625020, de64_FCMLA8h_elem(DA_V(0), DA_V(1), DA_V(2), 1, 180));
TEST(0x6f627020, de64_FCMLA8h_elem(DA_V(0), DA_V(1), DA_V(2), 1, 270));
TEST(0x6f421820, de64_FCMLA8h_elem(DA_V(0), DA_V(1), DA_V(2), 2, 0));
TEST(0x6f423820, de64_FCMLA8h_elem(DA_V(0), DA_V(1), DA_V(2), 2, 90));
TEST(0x6f425820, de64_FCMLA8h_elem(DA_V(0), DA_V(1), DA_V(2), 2, 180));
TEST(0x6f427820, de64_FCMLA8h_elem(DA_V(0), DA_V(1), DA_V(2), 2, 270));
TEST(0x6f621820, de64_FCMLA8h_elem(DA_V(0), DA_V(1), DA_V(2), 3, 0));
TEST(0x6f623820, de64_FCMLA8h_elem(DA_V(0), DA_V(1), DA_V(2), 3, 90));
TEST(0x6f625820, de64_FCMLA8h_elem(DA_V(0), DA_V(1), DA_V(2), 3, 180));
TEST(0x6f627820, de64_FCMLA8h_elem(DA_V(0), DA_V(1), DA_V(2), 3, 270));
TEST(0x6f821020, de64_FCMLA4s_elem(DA_V(0), DA_V(1), DA_V(2), 0, 0));
TEST(0x6f823020, de64_FCMLA4s_elem(DA_V(0), DA_V(1), DA_V(2), 0, 90));
TEST(0x6f825020, de64_FCMLA4s_elem(DA_V(0), DA_V(1), DA_V(2), 0, 180));
TEST(0x6f827020, de64_FCMLA4s_elem(DA_V(0), DA_V(1), DA_V(2), 0, 270));
TEST(0x6f821820, de64_FCMLA4s_elem(DA_V(0), DA_V(1), DA_V(2), 1, 0));
TEST(0x6f823820, de64_FCMLA4s_elem(DA_V(0), DA_V(1), DA_V(2), 1, 90));
TEST(0x6f825820, de64_FCMLA4s_elem(DA_V(0), DA_V(1), DA_V(2), 1, 180));
TEST(0x6f827820, de64_FCMLA4s_elem(DA_V(0), DA_V(1), DA_V(2), 1, 270));
TEST(0, de64_FCMLA4h_elem(DA_V(0), DA_V(1), DA_V(2), 2, 0));
TEST(0, de64_FCMLA4h_elem(DA_V(0), DA_V(1), DA_V(2), 3, 0));
TEST(0, de64_FCMLA8h_elem(DA_V(0), DA_V(1), DA_V(2), 4, 0));
TEST(0, de64_FCMLA8h_elem(DA_V(0), DA_V(1), DA_V(2), 5, 0));
TEST(0, de64_FCMLA4s_elem(DA_V(0), DA_V(1), DA_V(2), 2, 0));
TEST(0, de64_FCMLA4s_elem(DA_V(0), DA_V(1), DA_V(2), 3, 0));
#endif
