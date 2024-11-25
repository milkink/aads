#include <iostream>
#include <vector>
#include <string>

// Function to build the LPS (Longest Prefix Suffix) array
std::vector<int> computeLPSArray(const std::string& pattern) {
    int M = pattern.size();
    std::vector<int> lps(M, 0);
    int len = 0; // length of the previous longest prefix suffix
    int i = 1;

    while (i < M) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

// KMP search function
void KMPSearch(const std::string& text, const std::string& pattern) {
    int N = text.size();
    int M = pattern.size();

    std::vector<int> lps = computeLPSArray(pattern);

    int i = 0; // index for text
    int j = 0; // index for pattern

    while (i < N) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == M) {
            std::cout << "Found pattern at index " << (i - j) << std::endl;
            j = lps[j - 1];
        } else if (i < N && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    std::string text, pattern;

    std::cout << "Enter the text: ";
    std::getline(std::cin, text);

    std::cout << "Enter the pattern to search: ";
    std::getline(std::cin, pattern);

    KMPSearch(text, pattern);

    return 0;
}
