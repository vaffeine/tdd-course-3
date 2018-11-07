/*
Given a phrase, count the occurrences of each word in that phrase. Ignore whitespaces and punctual symbols
For example for the input "olly olly in come free please please let it be in such manner olly"
olly: 3
in: 2
come: 1
free: 1
please: 2
let: 1
it: 1
be: 1
manner: 1
such: 1
*/

#include <gtest/gtest.h>
#include <string>
#include <map>

std::map<std::string, uint32_t> count_words(const std::string &phrase) {
    std::map<std::string, uint32_t> result;
    return result;
}

TEST(count_words, test_empty_string_ret_empty_map) {
    std::map<std::string, uint32_t> expected;
    ASSERT_EQ(count_words(""), expected);
}

