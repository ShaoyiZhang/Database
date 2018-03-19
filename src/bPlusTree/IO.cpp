#include "string.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cstdio>
using namespace std;

string getLine(const string& filename, unsigned int startLine, unsigned int pageSize) {
    unsigned int replacePos = 0; // line number

    // open file
    FILE * pFile;
    pFile = fopen ( filename.c_str() , "r" );

    // go to startLine and read the line
    long int offset = (startLine-1)*pageSize;
    fseek ( pFile , offset , SEEK_SET );
    char * cLine = new char[pageSize];
    fgets (cLine, pageSize, pFile);
    // cout << cLine << endl;

    // if thisLine is NOT for the word passed in, return 0 (not found)
    string thisLine(cLine);
    return thisLine;
}
size_t fileSize(const char* sFileName)
{
  ifstream f;
  f.open(sFileName, ios_base::binary | ios_base::in);
  if (!f.good() || f.eof() || !f.is_open()) { return 0; }
  f.seekg(0, ios_base::beg);
  ifstream::pos_type begin_pos = f.tellg();
  f.seekg(0, ios_base::end);
  return static_cast<size_t>(f.tellg() - begin_pos);
}

size_t locInLine(const string& thisLine, unsigned int docID) {
    string idStr = to_string(docID) + " ";
    int repSize = idStr.size();
    string repStr = string(repSize, '-');
    return thisLine.find(repStr);
}
unsigned int insertDist(const string& filename,unsigned int startLine, unsigned int pageSize,const string& word, unsigned int docID){
    unsigned int replacePos = 0; // line number

    // open file
    FILE * pFile;
    pFile = fopen ( filename.c_str() , "r+" );

    // go to startLine and read the line
    long int offset = (startLine-1)*pageSize;
    fseek ( pFile , offset , SEEK_SET );
    char * cLine = new char[pageSize];
    fgets (cLine, pageSize, pFile);
    cout << cLine << endl;

    // if thisLine is NOT for the word passed in, return 0 (not found)
    string thisLine(cLine);
    bool isSameWord = (thisLine.find(word) == 0 );
    cout << (isSameWord?"true":"false") << endl;

    if (!isSameWord) {
        cerr << "startLine does not contain this word!\n";
        cerr << "create an overflow page for this word!\n";
        // return replacePos;
    }

    // while still the same word but no enough space => fseek down

    while (isSameWord) {
        size_t loc = locInLine(thisLine, docID);
        cout << "loc: " << loc << endl;
        if ( loc != string::npos) {
          // replace it
          fseek( pFile, offset + loc, SEEK_SET);
          fputs( (to_string(docID) + " ").c_str(), pFile);
          replacePos = offset;
          fclose( pFile );
          return replacePos;
        }
        offset += pageSize;
        fseek ( pFile , offset , SEEK_SET );
        char * cLine = new char[pageSize];
        fgets (cLine, pageSize + 1, pFile);
        string temp(cLine);
        thisLine = cLine;
        isSameWord = (thisLine.find(word) == 0);
    }
    // create overflow page
    size_t fileBitSize = fileSize(filename.c_str());
    replacePos = (unsigned int)fileBitSize/pageSize + 1;
    cout << "now creating overflow page at line: " << replacePos << "+1" << endl;
    // cout << "go to bit address: "
    fseek (pFile, (replacePos+1)*pageSize, SEEK_SET);
    string newLine = word + " " + to_string(docID) + " \n";
    cout << "newline" << " " << newLine;
    fputs (newLine.c_str(), pFile);
    fclose ( pFile );
    return replacePos;
}

// int main(){
//     insertDist("text", 6, 10, "e", 7);
//     return 0;
// }
