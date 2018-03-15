//
//  main.cpp
//  test
//
//  Created by Kay Wen on 3/14/18.
//  Copyright © 2018 Wen, Nuan. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, const char * argv[]) {
//    cout << (1? "true": "false");

    string thisLine = "DOC111001 - This, is a !! () (sample string.";
    vector<char> thisLineVec(thisLine.begin(), thisLine.end());
    thisLineVec.push_back('\0');
    char* cThisLine = &thisLineVec[0];
    // 2. get doc ID by tokenize it
    char * word = strtok (cThisLine," ,.-!()"); // first word must be DOC ID
    cout << word << endl;
    string wordStr = string(word);
    size_t docID = (size_t) stoi(wordStr.substr(3));
    cout << docID << endl;

    // 3. deal with the rest words of the same line
    word = strtok (NULL, " ,.-!()");
    while (word != NULL) {
        // ignore all words with length >= 256
        if (strlen(word) >= 256) {
            continue;
        }
        // deal with normal word
        size_t hashedVal = hash<string>{}(word);
        cout << hashedVal << " " << word << endl;
        // iteration
        word = strtok (NULL, " ,.-!()");
    }

//    string id = "0";
//    size_t idNum;
//    idNum = (size_t)stoi(id);
//    cout << idNum;
    return 0;
}
