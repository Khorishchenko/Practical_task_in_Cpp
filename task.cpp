#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <cctype>
 
 
bool isPunctuation(char ch) {
    return std::ispunct(static_cast<unsigned char>(ch));
}
 
 
void toLowerCase(std::string& str) {
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::tolower(c); });
}
 
int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open file input.txt" << std::endl;
        return 1;
    }
 
    std::map<std::string, int> wordCount;
    std::string word;
 
    
    while (inputFile >> word) {
        word.erase(std::remove_if(word.begin(), word.end(), isPunctuation), word.end());
 
        
        toLowerCase(word);
 
        if (!word.empty()) {
            wordCount[word]++;
        }
    }
 
    inputFile.close();
 
    
    std::string mostFrequentWord;
    int maxFrequency = 0;
    for (const auto& entry : wordCount) {
        if (entry.second > maxFrequency) {
            mostFrequentWord = entry.first;
            maxFrequency = entry.second;
        }
    }
 
    
    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open file output.txt" << std::endl;
        return 1;
    }
 
    outputFile << "Word\t\tFrequency\n";
    outputFile << "-------------------------\n";
    for (const auto& entry : wordCount) {
        outputFile << entry.first << "\t\t" << entry.second << "\n";
    }
    outputFile << "\nMost frequent word: " << mostFrequentWord
<< " (" << maxFrequency << " times)" << std::endl;
 
    outputFile.close();
 
    std::cout << "Results written to file output.txt" << std::endl;
 
    return 0;
}





void to_lowercase(std::string &str) {
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return std::tolower(c); });
}

int main() {
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");
    
    if (!inputFile.is_open()) {
        std::cerr << "Не вдалося відкрити файл для читання." << std::endl;
        return 1;
    }

    if (!outputFile.is_open()) {
        std::cerr << "Не вдалося відкрити файл для запису." << std::endl;
        return 1;
    }

    std::map<std::string, int> wordCount;
    std::string word;
    
    while (inputFile >> word) {
        to_lowercase(word);
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
        wordCount[word]++;
    }

    inputFile.close();

    for (const auto &pair : wordCount) {
        outputFile << pair.first << ": " << pair.second << std::endl;
    }

    auto maxElement = std::max_element(wordCount.begin(), wordCount.end(),
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) -> bool {
            return a.second < b.second;
        });

    if (maxElement != wordCount.end()) {
        outputFile << "Найбільш часто вживане слово: " << maxElement->first << " (кількість: " << maxElement->second << ")" << std::endl;
    }

    outputFile.close();
    std::cout << "Результат записано в файл output.txt" << std::endl;

    return 0;
}