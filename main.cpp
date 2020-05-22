// Programmer: Jessmer John Palanca
// Description: This program generates a probabilistic text that is
//              based on a given source text file. The program will
//              display a text that is somewhat similar content from
//              the source text file.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <cstdlib>
#include <time.h>


using namespace std;


// This function reads the text from the file, line by line.
// It splits every character of the text, and store each character
// into one string variable called "theText".

string readfile(string filename) {
    ifstream readFile(filename);
    string oneLine{""};
    string theText{""};

    if (readFile.is_open()) {
        bool isFirstLine = true;
        while (getline(readFile, oneLine)) {
            if (isFirstLine) {
                theText = theText + oneLine + " ";
                isFirstLine = false;
            } else {
                theText = theText + " " + oneLine + " ";
            }
        }
        readFile.close();
    } else {
        cout << "ERROR: Unable to read file " << "'" << filename << "'!A" << endl;
    }

    return theText;
}


// This function takes a string "theText" and an int which is the length of the nGram.
// It creates and return an unordered map where the key is a string, which has the length of nGram value.
// The value is a vector of character, that is the possible character(s) followed after the
// string "key".

unordered_map<string, vector<char>> createMap(string theText, int nGram) {
    unordered_map<string, vector<char>> wordMap;

    for (auto i = 0; i < theText.size() - nGram; i++) {
        string prefix = theText.substr(i, nGram);
        char suffix = theText[i + nGram];
        //key doesnt exist
        if (wordMap.count(prefix) == 0) {
            wordMap[prefix] = vector<char>();
            wordMap[prefix].push_back(suffix);
        }
            //key exist
        else {
            wordMap[prefix].push_back(suffix);
        }
    }

    return wordMap;
}


// This function generetes the the probabalistic text using the built in random number generator.
// The generated text will depend on the random number that's being generated. This function takes
// an int as the number of character that will be generated. In each iteration, the function will
// check if the key is in the unordered map. If the key is found, it will check for the vector
// value. The random number generated will be used as the index for the vector. The chosen value
// will be appended to the string called "theText". The string will be displayed approximately 60
// characters per line.

void generateText(unordered_map<string, vector<char>> wordMap, string theText, int nGram, int numChars) {
    string initial = theText.substr(0, nGram);
    string finalText = initial;
    srand((int) time(nullptr));
    auto i = 0;
    int randomNumber = 0;

    while (i < numChars) {
        auto difference = finalText.length() - nGram;
        auto key = finalText.substr(difference, nGram);

        if (wordMap.count(key) == 0) {
            finalText += " " + initial;
        }

        for (auto x : wordMap) {
            if (key == x.first) {
                auto vectorSize = x.second.size();
                if (vectorSize == 1) {
                    finalText += x.second[0];
                } else {
                    randomNumber = rand() % vectorSize;
                    finalText += x.second[randomNumber];
                }
            }
        }
        i++;
    }

    auto itr = 0;
    bool newLine = true;
    string whiteSpace{" "};
    while (itr < finalText.size()) {
        if (((itr + 1) % 60 == 0) or newLine == false) {
            whiteSpace = finalText[itr];
            newLine = false;
            if (whiteSpace == " ") {
                cout << finalText[itr] << endl;
                newLine = true;
            } else {
                cout << finalText[itr];
            }

        } else if (itr == finalText.size() - 1) {
            cout << finalText[itr] << endl;
        } else {
            cout << finalText[itr];
        }
        itr++;
    }
}

int main() {

    string filename;
    int nGram;
    int numChars;
    string fileInput;
    unordered_map<string, vector<char>> word_map;

    cout << "File name: ";
    cin >> filename;

    cout << "Enter ngram length: ";
    cin >> nGram;

    cout << "Letters to generate: ";
    cin >> numChars;

    fileInput = readfile(filename + ".txt");
    word_map = createMap(fileInput, nGram);
    generateText(word_map, fileInput, nGram, numChars);

    return 0;
}