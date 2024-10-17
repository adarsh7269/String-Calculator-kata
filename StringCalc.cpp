#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

class StringCalculator {
public:
    int Add(const std::string& numbers) {
        if (numbers.empty()) {
            return 0;
        }

        std::vector<std::string> delimiters = { ",", "\n" };
        std::string numString = numbers;

        if (numString.substr(0, 2) == "//") {
            // Check for custom delimiters
            if (numString.find("[") != std::string::npos) {
                size_t startingIndex = numString.find("[") + 1;
                size_t endingIndex = numString.find("]");
                std::string delimiter = numString.substr(startingIndex, endingIndex - startingIndex);

                numString = numString.substr(endingIndex + 2);
                return SumWithDelimiter(numString, delimiter);
            } else {
                // Single character custom delimiter
                std::string delimiter = numString.substr(2, 1);
                delimiters[0] = delimiter;
                delimiters[1] = delimiter;

                numString = numString.substr(4);
            }
        }

        return SumWithDelimiters(numString, delimiters);
    }

private:
    int SumWithDelimiter(const std::string& numbers, const std::string& delimiter) {
        std::vector<int> negatives;
        int sum = 0;

        std::vector<std::string> splitNumbers = Split(numbers, delimiter);

        for (const auto& num : splitNumbers) {
            int number = std::stoi(num);

            if (number < 0) {
                negatives.push_back(number);
            }

            if (number <= 1000) {
                sum += number;
            }
        }

        if (!negatives.empty()) {
            ThrowNegativesException(negatives);
        }

        return sum;
    }

    int SumWithDelimiters(const std::string& numbers, const std::vector<std::string>& delimiters) {
        std::vector<int> negatives;
        int sum = 0;

        std::vector<std::string> splitNumbers = Split(numbers, delimiters);

        for (const auto& num : splitNumbers) {
            int number = std::stoi(num);

            if (number < 0) {
                negatives.push_back(number);
            }

            if (number <= 1000) {
                sum += number;
            }
        }

        if (!negatives.empty()) {
            ThrowNegativesException(negatives);
        }

        return sum;
    }

    std::vector<std::string> Split(const std::string& str, const std::string& delimiter) {
        std::vector<std::string> result;
        size_t start = 0;
        size_t end = str.find(delimiter);

        while (end != std::string::npos) {
            result.push_back(str.substr(start, end - start));
            start = end + delimiter.length();
            end = str.find(delimiter, start);
        }

        result.push_back(str.substr(start, end));
        return result;
    }

    std::vector<std::string> Split(const std::string& str, const std::vector<std::string>& delimiters) {
        std::vector<std::string> result;
        std::string temp = str;

        for (const auto& delimiter : delimiters) {
            size_t pos = 0;

            while ((pos = temp.find(delimiter)) != std::string::npos) {
                result.push_back(temp.substr(0, pos));
                temp.erase(0, pos + delimiter.length());
            }
        }

        if (!temp.empty()) {
            result.push_back(temp);
        }

        return result;
    }

    void ThrowNegativesException(const std::vector<int>& negatives) {
        std::string message = "Negatives not allowed: ";

        for (size_t i = 0; i < negatives.size(); ++i) {
            message += std::to_string(negatives[i]);
            if (i < negatives.size() - 1) {
                message += ",";
            }
        }

        throw std::runtime_error(message);
    }
};

// Example usage:
// int main() {
//     StringCalculator calc;
//     try {
//         std::cout << calc.Add("//[***]\n1***2***-3") << std::endl;
//     } catch (const std::runtime_error& e) {
//         std::cerr << e.what() << std::endl;
//     }
//     return 0;
// }
