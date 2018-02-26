#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
// #include "?.h" // ?.h

int main(int argc,char* argv[])
{
    
    std::string indexFile = "";  // should be a class object
    while (!std::cin.eof()) {
        string thisLine;
        std::cin.getline(thisLine, 1000);
        if (std::thisLine.find("quit") != std::string::npos) { // > quit: close the console.
            exit(0);
        }
        else if (std::thisLine.find("load") != std::string::npos) { // > load [index file]: Loads a B+ index.
            indexFile = thisLine.substr(thisLine.find("load")+5);
            load(indexFile);
        }
        else if (std::thisLine.find("merge") != std::string::npos) { // > merge [index file]: Merge the current index file with the second index file, and update the index file on the disk.
            string indexFile_merge = thisLine.substr(thisLine.find("merge")+6);
            merge(indexFile, indexFile_merge);
            // merge(string&, string&) adds content of the second index file to the first index file
        }
        else if (std::thisLine.find("insert") != std::string::npos) { // > insert [document name]: Insert the word:document name pair into the index.
            std::string docFileName = thisLine.substr(thisLine.find("insert")+7);
            load(indexFile, docFileName);
            // assume that load takes the address of the new document and adds its contents into the index file
        }
        else if (std::thisLine.find("delete") != std::string::npos) { // delete [document name]: Removes a document with the given name from the index
            std::string docName = thisLine.substr(thisLine.find("delete")+7);
            delete(indexFile, docName);
            // assume that delete takes document IDS (DOCXX) and delete all related content from the index file
        }
        else if (std::thisLine.find("count") != std::string::npos) { // > count [keyword]: Counts a keyword by printing the number of documents that contain this keyword
            std::string keyword = thisLine.substr(thisLine.find("count")+6);
            count(indexFile, keyword);
        }
        else if (std::thisLine.find("count") != std::string::npos) { // > count [keyword]: Counts a keyword by printing the number of documents that contain this keyword
            std::string keyword = thisLine.substr(thisLine.find("count")+6);
            count(indexFile, keyword);
        }
        else if (std::thisLine.find("search") != std::string::npos) { // > search [keyword1, keyword2, ...]: Search multiple key words. Prints the name(s) of documents that contain all of these keywords
            std::string keywords = thisLine.substr(thisLine.find("search")+7);
            vector<std::string> keywordsVec;
            splitStrToVec_whitespace(keywordsVec, keywords);
            count(indexFile, keywordsVec);
        }
        else if (std::thisLine.find("printpath") != std::string::npos) { // > printpath [keyword]: Prints the search path (the id of pages that are accessed when we search the keyword in the B+ tree)
            std::string keyword = thisLine.substr(thisLine.find("printpath")+11);
            printPath(indexFile, keyword);// print page id
        }
        else if (std::thisLine.find("page") != std::string::npos) { // > page [i]: Displays the contents of the ith page
            std::string pageNumS = thisLine.substr(thisLine.find("page")+5);
            int pageNum = stoi(pageNumS);
            page(indexFile, pageNum);
        }
        else if (std::thisLine.find("range") != std::string::npos) { // > range [keyword1, keyword2]: Range query. Print all of the keywords between keyword1 and keyword2 where keyword1 < keyword2
            std::string keywords = thisLine.substr(thisLine.find("range")+6);
            vector<std::string> keywordsVec;
            splitStrToVec_whitespace(keywordsVec, keywords);
            if (keywordsVec.size() != 2) {
                std::cout << "please provide two keywords!\n";
                continue;
            } else {
                range(indexFile, keywordsVec[0], keywordsVec[2]);
            }
        }
        /*
        In addition to any output, you should print 1) the time it takes to perform the operation, 2) number of pages
        accessed, including pages in buffer, 3) number of pages read from or written to disk.
        */
        // implement these in database class?

    }
    return 0;
}

void splitStrToVec_whitespace(std::vector<std::string> &v, const string& str) {
    istringstream iss(str);
    std::copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(v));
}
