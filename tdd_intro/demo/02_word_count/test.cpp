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
    std::istringstream phrase_iss(phrase);
    std::vector<std::string> words {
        std::istream_iterator<std::string>(phrase_iss),
        std::istream_iterator<std::string>()
    };
    for (auto &word: words) {
        result[word] += 1;
    }
    return result;
}

TEST(count_words, test_empty_string_ret_empty_map) {
    std::map<std::string, uint32_t> expected;
    ASSERT_EQ(count_words(""), expected);
}

TEST(count_words, test_one_word_ret_one_word) {
    std::string word = "olly";
    std::map<std::string, uint32_t> expected = {{word, 1}};
    ASSERT_EQ(count_words(word), expected);
}

TEST(count_words, test_multiple_words_ret_correct) {
    std::string phrase = "olly olly in come free please please let it be in such manner olly";
    std::map<std::string, uint32_t> expected = {
        {"olly", 3},
        {"in", 2},
        {"come", 1},
        {"free", 1},
        {"please", 2},
        {"let", 1},
        {"it", 1},
        {"be", 1},
        {"manner", 1},
        {"such", 1},
    };
    ASSERT_EQ(count_words(phrase), expected);
}

