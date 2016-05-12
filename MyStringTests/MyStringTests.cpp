#include "stdafx.h"
#include "../MyString/MyString.h"
#include <string>

void VerifyMyString(const CMyString & s, const char *expectedData, size_t expectedLenght)
{
	BOOST_REQUIRE_EQUAL(s.GetLength(), expectedLenght);
	BOOST_REQUIRE_EQUAL(s.GetStringData(), expectedData);
	BOOST_REQUIRE_EQUAL(std::memcmp(s.GetStringData(), expectedData, expectedLenght + 1), 0);
}

BOOST_AUTO_TEST_SUITE(MyString_class_)

	BOOST_AUTO_TEST_CASE(can_be_created_with_zero_terminated_symbol)
	{
		CMyString myStr("\0");
		VerifyMyString(myStr, "\0", 0);
	}

	BOOST_AUTO_TEST_CASE(my_string_with_zero_terminated_symbol_will_be_cut)
	{
		CMyString myStr("Test\0 String");
		VerifyMyString(myStr, "Test", 4);
	}
	struct create_by_default_
	{
		CMyString myString;
	};

	BOOST_FIXTURE_TEST_SUITE(by_default, create_by_default_)

		BOOST_AUTO_TEST_CASE(length_of_string_equal_to_zero)
		{
			BOOST_CHECK_EQUAL(myString.GetLength(), 0);
		}

		BOOST_AUTO_TEST_CASE(my_str_have_a_zero_terminated_symbol)
		{
			BOOST_CHECK_EQUAL(myString.GetStringData()[myString.GetLength()], '\0');
		}

		BOOST_AUTO_TEST_CASE(substring_returns_nullptr_and_zero_length)
		{
			VerifyMyString(myString.SubString(0, 5), "\0", 0);
		}

		BOOST_AUTO_TEST_CASE(can_be_cleared)
		{
			myString.Clear();
			VerifyMyString(myString, "\0", 0);
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct can_be_declared_by_char_array_
	{
		can_be_declared_by_char_array_()
			: myString("Test String")
		{};

		CMyString myString;
	};

	BOOST_FIXTURE_TEST_SUITE(can_be_declared_by_char_array, can_be_declared_by_char_array_)

		BOOST_AUTO_TEST_CASE(has_length_equal_to_length_of_char_array_that_putted_to_myStr_constructor_and_data_same_to_that)
		{
			VerifyMyString(myString, "Test String", 11);
		}

		BOOST_AUTO_TEST_CASE(can_returns_substring_of_myString)
		{
			VerifyMyString(myString.SubString(0, 4), "Test", 4);
		}

		BOOST_AUTO_TEST_CASE(returns_terminated_str_substring_with_incorrect_args)
		{
			VerifyMyString(myString.SubString(4, 4), "\0", 0);
			VerifyMyString(myString.SubString(10, 4), "\0", 0);
			VerifyMyString(myString.SubString(0), "\0", 0);
		}

		BOOST_AUTO_TEST_CASE(have_a_zero_terminated_symbol_at_the_end)
		{
			BOOST_CHECK_EQUAL(myString.GetStringData()[myString.GetLength()], '\0');
		}

		BOOST_AUTO_TEST_CASE(can_be_cleared)
		{
			myString.Clear();
			VerifyMyString(myString, "\0", 0);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(my_string_with_zero_terminated_symbol_will_not_be_cut_if_length_of_str_will_be_putted_in_constructor)
	{
		CMyString myStr("Test\0 String", 12);
		VerifyMyString(myStr, "Test\0 String", 12);
	}

	struct can_be_declared_by_char_array_and_length_
	{
		can_be_declared_by_char_array_and_length_()
			: myString("Test String12345", 11)
		{};

		CMyString myString;
	};

	BOOST_FIXTURE_TEST_SUITE(can_be_declared_by_char_array_and_length, can_be_declared_by_char_array_and_length_)

		BOOST_AUTO_TEST_CASE(has_length_equal_to_length_that_putted_to_myStr_constructor_and_data_same_to_putted)
		{
			VerifyMyString(myString, "Test String", 11);
		}

		BOOST_AUTO_TEST_CASE(can_returns_substring_of_myString)
		{
			VerifyMyString(myString.SubString(0, 4), "Test", 4);
		}

		BOOST_AUTO_TEST_CASE(returns_terminated_str_substring_with_incorrect_args)
		{
			VerifyMyString(myString.SubString(4, 4), "\0", 0);
			VerifyMyString(myString.SubString(10, 4), "\0", 0);
			VerifyMyString(myString.SubString(0), "\0", 0);
		}

		BOOST_AUTO_TEST_CASE(have_a_zero_terminated_symbol_at_the_end)
		{
			BOOST_CHECK_EQUAL(myString.GetStringData()[myString.GetLength()], '\0');
		}

		BOOST_AUTO_TEST_CASE(can_be_cleared)
		{
			myString.Clear();
			VerifyMyString(myString, "\0", 0);
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct can_be_copied_by_other_myString_
	{
		can_be_copied_by_other_myString_()
			: other("Test String", 11)
			, myString(other)
		{
		};

		CMyString other;
		CMyString myString;
	};

	BOOST_FIXTURE_TEST_SUITE(can_be_copied_by_other_myString, can_be_copied_by_other_myString_)

		BOOST_AUTO_TEST_CASE(has_length_equal_to_length_that_putted_myString)
		{
			VerifyMyString(myString, "Test String", 11);
		}

		BOOST_AUTO_TEST_CASE(can_returns_substring_of_myString)
		{
			VerifyMyString(myString.SubString(0, 4), "Test", 4);
		}

		BOOST_AUTO_TEST_CASE(returns_terminated_str_substring_with_incorrect_args)
		{
			VerifyMyString(myString.SubString(4, 4), "\0", 0);
			VerifyMyString(myString.SubString(10, 4), "\0", 0);
			VerifyMyString(myString.SubString(0), "\0", 0);
		}

		BOOST_AUTO_TEST_CASE(have_a_zero_terminated_symbol_at_the_end)
		{
			BOOST_CHECK_EQUAL(myString.GetStringData()[myString.GetLength()], '\0');
		}

		BOOST_AUTO_TEST_CASE(can_be_cleared)
		{
			myString.Clear();
			VerifyMyString(myString, "\0", 0);
		}

	BOOST_AUTO_TEST_SUITE_END()


	struct can_be_moved_from_other_myString_
	{
		can_be_moved_from_other_myString_()
			: myString(CMyString("Test String", 11))
		{
		};

		CMyString myString;
	};

	BOOST_FIXTURE_TEST_SUITE(can_be_moved_from_other_myString, can_be_moved_from_other_myString_)

		BOOST_AUTO_TEST_CASE(has_length_equal_to_length_that_putted_myString)
		{
			VerifyMyString(myString, "Test String", 11);
		}

		BOOST_AUTO_TEST_CASE(can_returns_substring_of_myString)
		{
			VerifyMyString(myString.SubString(0, 4), "Test", 4);
		}

		BOOST_AUTO_TEST_CASE(returns_terminated_str_substring_with_incorrect_args)
		{
			VerifyMyString(myString.SubString(4, 4), "\0", 0);
			VerifyMyString(myString.SubString(10, 4), "\0", 0);
			VerifyMyString(myString.SubString(0), "\0", 0);
		}

		BOOST_AUTO_TEST_CASE(have_a_zero_terminated_symbol_at_the_end)
		{
			BOOST_CHECK_EQUAL(myString.GetStringData()[myString.GetLength()], '\0');
		}

		BOOST_AUTO_TEST_CASE(can_be_cleared)
		{
			myString.Clear();
			VerifyMyString(myString, "\0", 0);
		}

	BOOST_AUTO_TEST_SUITE_END()


	struct can_be_copied_from_stl_string_
	{
		can_be_copied_from_stl_string_()
			: stlString("Test String")
			, myString(stlString)
		{
		};

		std::string stlString;
		CMyString myString;
	};

	BOOST_FIXTURE_TEST_SUITE(can_be_copied_from_stl_string, can_be_copied_from_stl_string_)

		BOOST_AUTO_TEST_CASE(has_length_equal_to_length_that_putted_myString)
		{
			VerifyMyString(myString, "Test String", 11);
		}

		BOOST_AUTO_TEST_CASE(can_returns_substring_of_myString)
		{
			VerifyMyString(myString.SubString(0, 4), "Test", 4);
		}

		BOOST_AUTO_TEST_CASE(returns_terminated_str_substring_with_incorrect_args)
		{
			VerifyMyString(myString.SubString(4, 4), "\0", 0);
			VerifyMyString(myString.SubString(10, 4), "\0", 0);
			VerifyMyString(myString.SubString(0), "\0", 0);
		}

		BOOST_AUTO_TEST_CASE(have_a_zero_terminated_symbol_at_the_end)
		{
			BOOST_CHECK_EQUAL(myString.GetStringData()[myString.GetLength()], '\0');
		}

		BOOST_AUTO_TEST_CASE(can_be_cleared)
		{
			myString.Clear();
			VerifyMyString(myString, "\0", 0);
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct have_assining_operator_
	{
		have_assining_operator_()
			: myString("something")
		{}

		CMyString myString;
	};

	BOOST_FIXTURE_TEST_SUITE(have_assining_operator, have_assining_operator_)

		BOOST_AUTO_TEST_CASE(can_be_assigned_by_other_MyString)
		{
			CMyString other("Test String");
			myString = other;
			VerifyMyString(other, "Test String", 11);
			VerifyMyString(myString, other.GetStringData(), other.GetLength());
		}

		BOOST_AUTO_TEST_CASE(can_be_assigned_by_moving_other_MyString)
		{
			myString = CMyString("Test String");
			VerifyMyString(myString, "Test String", 11);
		}

		BOOST_AUTO_TEST_CASE(can_be_assigned_itself)
		{
			myString = myString;
			VerifyMyString(myString.GetStringData(), "something", 9);
		}
		
	BOOST_AUTO_TEST_SUITE_END()

	struct have_unary_and_binary_addition_operator_
	{
		have_unary_and_binary_addition_operator_()
			: myString("something")
		{}

		CMyString myString;
	};

	BOOST_FIXTURE_TEST_SUITE(have_unary_and_binary_addition_operator, have_unary_and_binary_addition_operator_)

		BOOST_AUTO_TEST_CASE(can_be_added_other_MyString)
		{
			CMyString other(" Test String");
			myString += other;
			VerifyMyString(other, " Test String", 12);
			VerifyMyString(myString, "something Test String", 9 + other.GetLength());

			myString = myString + other;
			VerifyMyString(other, " Test String", 12);
			VerifyMyString(myString, "something Test String Test String", 9 + 2 * other.GetLength());
		}

		BOOST_AUTO_TEST_CASE(can_be_added_stl_string)
		{
			std::string other(" Test String");
			myString = myString + other;
			VerifyMyString(myString, "something Test String", 9 + other.length());
		}

		BOOST_AUTO_TEST_CASE(can_be_added_char_array)
		{
			char * other = " Test String";
			myString = myString + other;
			VerifyMyString(myString, "something Test String", 9 + strlen(other));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(comparison_operator)

		BOOST_AUTO_TEST_CASE(strings_are_equal)
		{
			BOOST_CHECK(CMyString("Test String") == CMyString("Test String", 11));
		}

		BOOST_AUTO_TEST_CASE(strings_are_not_equal)
		{
			BOOST_CHECK(!(CMyString("Test String1") == CMyString("Test String", 11)));
		}

		BOOST_AUTO_TEST_CASE(zero_terminated_symbol_wont_be_ignored)
		{
			BOOST_CHECK(!(CMyString("Test") == CMyString("Test\0 String", 12)));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(inequality_operator)

		BOOST_AUTO_TEST_CASE(strings_are_equal)
		{
			BOOST_CHECK(!(CMyString("Test String") != CMyString("Test String", 11)));
		}

		BOOST_AUTO_TEST_CASE(strings_are_not_equal)
		{
			BOOST_CHECK(CMyString("Test String1") != CMyString("Test String", 11));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(less_operator)

		BOOST_AUTO_TEST_CASE(can_find_out_which_of_rows_preceded_by_another_in_alphabetical_order)
		{
			BOOST_CHECK((CMyString("ab") < CMyString("abc")));
		}

		BOOST_AUTO_TEST_CASE(left_str_is_not_less_by_right_str)
		{
			BOOST_CHECK(!(CMyString("abz") < CMyString("abcd", 3)));
		}

		BOOST_AUTO_TEST_CASE(if_strings_is_equal_operator_less_return_false)
		{
			BOOST_CHECK(!(CMyString("Test", 4) < CMyString("Test")));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(more_operator)

		BOOST_AUTO_TEST_CASE(can_find_out_which_of_rows_preceded_by_another_in_alphabetical_order)
		{
			BOOST_CHECK((CMyString("abc") > CMyString("ab")));
		}

		BOOST_AUTO_TEST_CASE(left_str_is_more_than_right_str)
		{
			BOOST_CHECK(CMyString("abz") > CMyString("abcd", 3));
		}

		BOOST_AUTO_TEST_CASE(if_strings_is_equal_operator_less_return_false)
		{
			BOOST_CHECK(!(CMyString("Test") > CMyString("Test")));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(more_or_equal_operator_and_less_or_equal)

		BOOST_AUTO_TEST_CASE(can_find_out_which_of_rows_preceded_by_another_in_alphabetical_order)
	{
		BOOST_CHECK((CMyString("abc") >= CMyString("ab")));
		BOOST_CHECK((CMyString("ab") <= CMyString("abc")));
	}

	BOOST_AUTO_TEST_CASE(left_str_is_more_than_right_str)
	{
		BOOST_CHECK(CMyString("abz") >= CMyString("abcd", 3));
		BOOST_CHECK(!(CMyString("abz") <= CMyString("abcd", 3)));
	}

	BOOST_AUTO_TEST_CASE(if_strings_is_equal_operator_less_return_false)
	{
		BOOST_CHECK(CMyString("Test") >= CMyString("Test"));
		BOOST_CHECK(CMyString("Test") <= CMyString("Test"));
	}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(have_indexed_acces_operator)
	{
		CMyString str("Test String");
		BOOST_CHECK(str[0] == 'T');
		str[0] = 'e';
		BOOST_CHECK(str[0] == 'e');
	}

	BOOST_AUTO_TEST_CASE(have_ostream_operator)
	{
		std::ostringstream strm;
		CMyString myString("Test String");
		strm << myString;
		BOOST_CHECK_EQUAL(strm.str(), "Test String");

		CMyString myString1("Test\0 String", 12);
		strm << myString1;
		BOOST_CHECK(strm.str() == "Test StringTest String");
	}

	BOOST_AUTO_TEST_CASE(have_isstream_operator)
	{
		CMyString myString;
		std::istringstream strm("TestString");
		strm >> myString;
		VerifyMyString(myString, "TestString", 10);

		std::istringstream strm1("");
		BOOST_CHECK(!(strm >> myString));
		VerifyMyString(myString, "TestString", 10);
	}

BOOST_AUTO_TEST_SUITE_END()