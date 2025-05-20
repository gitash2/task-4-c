//
// Created by ash on 5/19/25.
//

#include "TextProcessor.h"
#include "Logger.h"
#include <QFile>
#include <QRegularExpression>
#include <algorithm>

namespace fs = std::filesystem;
fs::path root = fs::current_path().root_path();
const std::string DEFAULT_SAVE_PATH = root / "results";


std::unordered_set<std::string> TextProcessor::loadKeywords(const std::string &filename) {
    std::unordered_set<std::string> keywords;
    std::ifstream file(filename);
    std::string word;
    while (file >> word) {
        std::transform(word.begin(), word.end(), word.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        keywords.insert(word);
    }
    return keywords;
}

std::map<std::string, std::vector<std::pair<int, int> > >
TextProcessor::processText(const std::string &filename,
                           const std::unordered_set<std::string> &keywords) {
    std::map<std::string, std::vector<std::pair<int, int> > > wordMap;

    QFile file(QString::fromStdString(filename));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Logger::log("Cannot open file: " + filename, "ERROR");
        return wordMap;
    }

    QTextStream in(&file);
    QRegularExpression re(QStringLiteral("\\p{L}+"));

    int row = 1;
    while (!in.atEnd()) {
        QString line = in.readLine();
        auto it = re.globalMatch(line);
        while (it.hasNext()) {
            QRegularExpressionMatch m = it.next();
            QString word = m.captured().toLower();
            int col = m.capturedStart() + 1;

            std::string wordStd = word.toStdString();
            if (!keywords.count(wordStd)) {
                wordMap[wordStd].emplace_back(row, col);
            }
        }
        ++row;
    }

    return wordMap;
}

std::string TextProcessor::generateUniqueFilename(const std::string &basePath) {
    if (!fs::exists(basePath)) {
        fs::create_directories(basePath);
    }

    auto now = std::chrono::system_clock::now();
    auto timeT = std::chrono::system_clock::to_time_t(now);
    std::ostringstream oss;
    oss << basePath << "output_" << std::put_time(std::localtime(&timeT), "%Y-%m-%d_%H-%M-%S") << ".txt";

    return oss.str();
}

void TextProcessor::saveResults(const std::map<std::string, std::vector<std::pair<int, int> > > &wordMap) {
    std::string filename = generateUniqueFilename(DEFAULT_SAVE_PATH);
    std::ofstream file(filename);
    for (const auto &entry: wordMap) {
        file << entry.first << " ";
        for (const auto &pos: entry.second) {
            file << "(" << pos.first << ", " << pos.second << ") ";
        }
        file << "\n";
    }
}

std::string TextProcessor::processFiles(const std::string &textFile, const std::string &keywordsFile) {
    auto keywords = loadKeywords(keywordsFile);
    auto wordMap = processText(textFile, keywords);
    saveResults(wordMap);
    return "Done. Result saved.";
}
