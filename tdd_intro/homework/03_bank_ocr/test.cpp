/*### Bank OCR

Your manager has recently purchased a machine that assists in reading letters and faxes sent in by branch offices. The machine scans the paper documents, and produces a file with a number of entries. You will write a program to parse this file.

#### Specification
#### User Story 1

The following format is created by the machine:
```
    _  _     _  _  _  _  _
  | _| _||_||_ |_   ||_||_|
  ||_  _|  | _||_|  ||_| _|
```
Each entry is 3 lines long, and each line has 27 characters. 3 lines of each entry contain an account number written using pipes and underscores.

Each account number should have 9 digits, all of which should be in the range 0-9. A normal file contains around 500 entries.

Write a program that can take this file and parse it into actual account numbers.

Example input and output
```
 _  _  _  _  _  _  _  _  _
| || || || || || || || || |
|_||_||_||_||_||_||_||_||_|

=> 000000000

  |  |  |  |  |  |  |  |  |
  |  |  |  |  |  |  |  |  |

=> 111111111

 _  _  _  _  _  _  _  _  _
 _| _| _| _| _| _| _| _| _|
|_ |_ |_ |_ |_ |_ |_ |_ |_

=> 222222222

 _  _  _  _  _  _  _  _  _
 _| _| _| _| _| _| _| _| _|
 _| _| _| _| _| _| _| _| _|

=> 333333333

|_||_||_||_||_||_||_||_||_|
  |  |  |  |  |  |  |  |  |

=> 444444444

 _  _  _  _  _  _  _  _  _
|_ |_ |_ |_ |_ |_ |_ |_ |_
 _| _| _| _| _| _| _| _| _|

=> 555555555

 _  _  _  _  _  _  _  _  _
|_ |_ |_ |_ |_ |_ |_ |_ |_
|_||_||_||_||_||_||_||_||_|

=> 666666666

 _  _  _  _  _  _  _  _  _
  |  |  |  |  |  |  |  |  |
  |  |  |  |  |  |  |  |  |

=> 777777777

 _  _  _  _  _  _  _  _  _
|_||_||_||_||_||_||_||_||_|
|_||_||_||_||_||_||_||_||_|

=> 888888888

 _  _  _  _  _  _  _  _  _
|_||_||_||_||_||_||_||_||_|
 _| _| _| _| _| _| _| _| _|

=> 999999999

    _  _     _  _  _  _  _
  | _| _||_||_ |_   ||_||_|
  ||_  _|  | _||_|  ||_| _|

=> 123456789
```
*/
#include <gtest/gtest.h>
#include <string>

const unsigned short g_digitLen = 3;
const unsigned short g_linesInDigit = 3;
struct Digit
{
    std::string lines[g_linesInDigit];
};

bool operator==(const Digit &lhs, const Digit &rhs) {
    for (size_t i = 0; i < g_linesInDigit; ++i) {
        if (lhs.lines[i] != rhs.lines[i]) {
            return false;
        }
    }

    return true;
}

const unsigned short g_digitsOnDisplay = 9;
struct Display
{
    std::string lines[g_linesInDigit];
};

const Digit s_digit0 = { " _ ",
                         "| |",
                         "|_|"
                       };
const Digit s_digit1 = { "   ",
                         "  |",
                         "  |"
                       };
const Digit s_digit2 = { " _ ",
                         " _|",
                         "|_ "
                       };
const Digit s_digit3 = { " _ ",
                         " _|",
                         " _|"
                       };
const Digit s_digit4 = { "   ",
                         "|_|",
                         "  |"
                       };
const Digit s_digit5 = { " _ ",
                         "|_ ",
                         " _|"
                       };
const Digit s_digit6 = { " _ ",
                         "|_ ",
                         "|_|"
                       };
const Digit s_digit7 = { " _ ",
                         "  |",
                         "  |"
                       };
const Digit s_digit8 = { " _ ",
                         "|_|",
                         "|_|"
                       };
const Digit s_digit9 = { " _ ",
                         "|_|",
                         " _|"
                       };

const Display s_displayAll0 = { " _  _  _  _  _  _  _  _  _ ",
                                "| || || || || || || || || |",
                                "|_||_||_||_||_||_||_||_||_|"
};

const Display s_displayAll1 = { "                           ",
                                "  |  |  |  |  |  |  |  |  |",
                                "  |  |  |  |  |  |  |  |  |"
};

const Display s_displayAll2 = {  " _  _  _  _  _  _  _  _  _ ",
                                 " _| _| _| _| _| _| _| _| _|",
                                 "|_ |_ |_ |_ |_ |_ |_ |_ |_ "
};

const Display s_displayAll3 = { " _  _  _  _  _  _  _  _  _ ",
                                " _| _| _| _| _| _| _| _| _|",
                                " _| _| _| _| _| _| _| _| _|"
};

const Display s_displayAll4 = { "                           ",
                                "|_||_||_||_||_||_||_||_||_|",
                                "  |  |  |  |  |  |  |  |  |"
};

const Display s_displayAll5 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_ |_ |_ |_ |_ |_ |_ |_ |_ ",
                                " _| _| _| _| _| _| _| _| _|"
};

const Display s_displayAll6 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_ |_ |_ |_ |_ |_ |_ |_ |_ ",
                                "|_||_||_||_||_||_||_||_||_|"
};

const Display s_displayAll7 = { " _  _  _  _  _  _  _  _  _ ",
                                "  |  |  |  |  |  |  |  |  |",
                                "  |  |  |  |  |  |  |  |  |"
};

const Display s_displayAll8 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_||_||_||_||_||_||_||_||_|",
                                "|_||_||_||_||_||_||_||_||_|"
};

const Display s_displayAll9 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_||_||_||_||_||_||_||_||_|",
                                " _| _| _| _| _| _| _| _| _|"
};

const Display s_display123456789 = { "    _  _     _  _  _  _  _ ",
                                     "  | _| _||_||_ |_   ||_||_|",
                                     "  ||_  _|  | _||_|  ||_| _|"
};

Digit get_digit(const Display &display, size_t index) {
    Digit result;
    for (size_t i = 0; i < g_linesInDigit; ++i) {
        result.lines[i] = display.lines[i].substr(3 * index, g_digitLen);
        for (auto c: result.lines[i]) {
            if (c != ' ' && c != '_' && c != '|') {
                throw std::runtime_error("Wrong char in digit");
            }
        }
    }
    return result;
}

const Digit s_allDigits[10] = {
    s_digit0, s_digit1, s_digit2, s_digit3, s_digit4,
    s_digit5, s_digit6, s_digit7, s_digit8, s_digit9
};

uint8_t parse_digit(const Digit &digit) {
    for (size_t i = 0; i < 10; ++i) {
        if (digit == s_allDigits[i]) {
            return i;
        }
    }

    return 10;
}

TEST(TestGetDigit, test_digit_has_3_columns) {
    Digit result = get_digit(s_displayAll0, 0);
    ASSERT_EQ(result.lines[0].size(), 3lu);
}

TEST(TestGetDigit, test_digit_has_3_rows) {
    Digit result = get_digit(s_displayAll0, 0);
    ASSERT_EQ(result.lines[0].size(), 3lu);
    ASSERT_EQ(result.lines[1].size(), 3lu);
    ASSERT_EQ(result.lines[2].size(), 3lu);
}

TEST(TestGetDigit, test_invalid_symbols_leads_to_exception) {
    const Display invalid_char_digit = { " _  _  _  _  _  _  _  _  _ ",
                                         "# || || || || || || || || |",
                                         "|#||_||_||_||_||_||_||_||_|"
    };
    ASSERT_THROW(get_digit(invalid_char_digit, 0), std::runtime_error);
}

TEST(TestGetDigit, test_5th_digit_is_5) {
    Digit result = get_digit(s_display123456789, 4);
    ASSERT_EQ(result, s_digit5);
}

TEST(TestParseDigit, test_digit0_is_0) {
    ASSERT_EQ(parse_digit(s_digit0), 0);
}

TEST(TestParseDigit, test_digit5_is_5) {
    ASSERT_EQ(parse_digit(s_digit5), 5);
}

TEST(TestParseDisplay, test_parse_123456789_display_is_9_length) {
    ASSERT_EQ(parse_display(s_display123456789).size(), g_digitsOnDisplay);
}

TEST(TestDigitOperEqual, test_that_same_digit_is_equal) {
    ASSERT_EQ(s_digit0, s_digit0);
}

TEST(TestDigitOperEqual, test_different_digits_are_not_equal) {
    ASSERT_FALSE(s_digit0 == s_digit8);
}
