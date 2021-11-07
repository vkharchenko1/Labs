#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <unordered_map>
#include <algorithm>
using namespace std;


int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "wrong input" << endl;
	}

	ifstream input(argv[1]);
	ofstream output(argv[2]);
	unordered_map<string, int> words;
	int word_count = 0;
	string line;
	string word = "";

	while (getline(input, line)) {
		for (auto letter : line) {
			if (isdigit(letter) || isalpha(letter) || letter == '\'')
				word += letter;
			else if (!word.empty()) {
				words[word] += 1;
				word = "";
				word_count++;
			}
		}
		if (!word.empty()) {
			words[word] += 1;
			word = "";
			word_count++;
		}
	}

	vector<pair<string, int>> dict(words.begin(), words.end());
	stable_sort(dict.begin(), dict.end(), [](const auto& a, const auto& b) -> bool {
			if (a.second == b.second)
				return a.first < b.first;
			return a.second > b.second;
		});
	
	for (auto c : dict) {
		output << c.first << ";" << c.second << ";" << (float)c.second / (float)word_count * 100 << "%" << endl;
	}
}