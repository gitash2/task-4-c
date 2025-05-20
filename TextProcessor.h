//
// Created by ash on 5/19/25.
//

#ifndef TEXTPROCESSOR_H
#define TEXTPROCESSOR_H

#include <string>
#include <unordered_set>
#include <map>
#include <vector>

class TextProcessor {
    friend class TextProcessorTest;
public:
    static std::string processFiles(const std::string &textFile, const std::string &keywordsFile);
    std::unordered_set<std::string> loadKeywordsForTest(const std::string &filename) {
        return loadKeywords(filename);
    }

    std::map<std::string, std::vector<std::pair<int, int>>> processTextForTest(const std::string &filename, const std::unordered_set<std::string> &keywords) {
        return processText(filename, keywords);
    }
    std::string generateUniqueFilenameForTest(const std::string &basePath) {
        return generateUniqueFilename(basePath);
    }

    std::string processFiles(const std::string & string, const std::string & basic_string, const std::string & to_std_string);

    static std::unordered_set<std::string> loadKeywords(const std::string &filename);

    static std::map<std::string, std::vector<std::pair<int, int>>> processText(const std::string &filename, const std::unordered_set<std::string> &keywords);
    static void saveResults(const std::map<std::string, std::vector<std::pair<int, int>>> &wordMap);
    static std::string generateUniqueFilename(const std::string &basePath);



};
#endif //TEXTPROCESSOR_H
