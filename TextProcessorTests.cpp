//
// Created by ash on 5/19/25.
//

#include <gtest/gtest.h>
#include "TextProcessor.h"
#include <fstream>

class TextProcessorTests : public ::testing::Test {
protected:
    void SetUp() override {
        std::ofstream keywordFile("test_keywords.txt");
        keywordFile << "apple\nbanana\n";
        keywordFile.close();

        std::ofstream textFile("test_text.txt");
        textFile << "apple orange banana grape\n"
                 << "orange apple grape banana\n";
        textFile.close();
    }

    void TearDown() override {
        remove("test_keywords.txt");
        remove("test_text.txt");
    }
};

TEST_F(TextProcessorTests, LoadKeywords) {
    TextProcessor tp;
    auto keywords = TextProcessor::loadKeywords("test_keywords.txt");
    EXPECT_EQ(keywords.size(), 2);
    EXPECT_TRUE(keywords.contains("apple"));
    EXPECT_TRUE(keywords.contains("banana"));
}

TEST_F(TextProcessorTests, ProcessText) {
    TextProcessor tp;
    auto keywords = TextProcessor::loadKeywords("test_keywords.txt");
    auto wordMap = TextProcessor::processText("test_text.txt", keywords);

    EXPECT_FALSE(wordMap.contains("apple"));
    EXPECT_FALSE(wordMap.contains("banana"));

    EXPECT_TRUE(wordMap.contains("orange"));
    EXPECT_TRUE(wordMap.contains("grape"));

    ASSERT_EQ(wordMap["orange"].size(), 2);
    EXPECT_EQ(wordMap["orange"][0], std::make_pair(1, 7));
    EXPECT_EQ(wordMap["orange"][1], std::make_pair(2, 1));

    ASSERT_EQ(wordMap["grape"].size(), 2);
}
