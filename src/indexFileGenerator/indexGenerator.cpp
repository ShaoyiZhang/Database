#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <iterator>
#include <algorithm>
#include <chrono>
using namespace std;

void buildIndex(const string& textFile, const string& indexFile, unsigned int pageSize);

// https://codereview.stackexchange.com/questions/159628/c-split-string-into-a-vector
vector<std::string> Split(const std::string& subject) {
    stringstream ss(subject);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    vector<string> vstrings(begin, end);
    copy(vstrings.begin(), vstrings.end(), vstrings.begin());
    return vstrings;
}

int main(int argc, const char * argv[]){
    unsigned long pageSize = 8096;
    while(!cin.eof()) {
        string thisLine;
        getline(cin,thisLine);
        if (thisLine.find("build index") != string::npos) {
            // parse command
            vector<string> parsedResult = Split(thisLine);
            vector<string>::iterator it;
            // check if "-p" is correctly set
            it = find (parsedResult.begin(), parsedResult.end(), "-p");
            if (it != parsedResult.end()) {
                // "-p" set
                it++;
                if (it != parsedResult.end()) {
                    // pageSize correctly obtained
                    try {
                        pageSize = stoul(*it);
                    } catch(exception& e) {
                        cout << "cannot do stoul invalid page size input, try again.\n";
                    }
                }
            } else {
                // no "-p", use default pageSize 8096
                if (parsedResult.size() != 4) {
                    cout << "invalid number of inputs, try again.\n";
                }
            }

            // cout << pageSize << endl;
            string indexFile = parsedResult.at(3);
            string textFile = parsedResult.at(2);
            buildIndex(textFile, indexFile, pageSize);

        } else if (thisLine.find("quit") != string::npos) {
            return 0;
        } else {
            cout << "invalid input, try again.\n";
        }
    }
}

void buildIndex(const string& textFile, const string& indexFile, unsigned int pageSize){
    auto start = std::chrono::system_clock::now();
    time_t start_time = chrono::system_clock::to_time_t(start);
// ========== read from data file ================
    map<string, unordered_set<unsigned int>> index;
    ifstream infile(textFile);
    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        vector<string> words{istream_iterator<string>{iss}, istream_iterator<string>{}};
        string doc = words[0];
        unsigned int line_no = stoi(doc.substr(3, doc.length()));
        // cerr << "l" << line_no << " ";
        for (vector<string>::iterator iter = words.begin() + 1; iter != words.end(); iter++) {
            if (sizeof(*iter)>=256) continue;
            index[*iter].insert(line_no);
   //       index[*iter].push_back(line_no);
        }
    }
    // cerr << "\n";
    infile.close();


    ofstream outfile(indexFile);
    ofstream helperIndex("word.line.index");

    unsigned long lineBuilt = 0; // number of line built so far
    string nextWord = "";
    for (auto &t: index) {
    // for (map<string, unordered_set<unsigned int>>) {
        lineBuilt++;
	// cerr << "lb" << lineBuilt << " ";
        outfile << t.first << "\t";
        helperIndex << t.first << " " << lineBuilt << "\n";
        // cerr << t.first << "\t";
        unsigned int currSize = 0; // byte size of current string line!!
        unsigned int idPrinted = 0;// number of ids printed
        unsigned int totalSize = t.second.size(); // total id num
        unsigned int lineNum = 0;

        currSize = (t.first+ "\t").size();

        if (currSize >= 256) continue;
        auto it = t.second.begin();

        while (idPrinted < totalSize) {
            if (currSize < pageSize - 8 ) {
                // always save some space at the end, make sure it's exactly pageSize per page(line)
                outfile << *it << " ";
                // cerr << *it << " ";
                currSize += ((to_string(*it) + " ").size());
                idPrinted++;
                it++;
            } else {
                lineBuilt++;
                // cerr << "lb" << lineBuilt << " ";
	       	       outfile << endl;
                // cerr << endl;
                outfile << t.first << "\t";
                // cerr << t.first << "\t";
                currSize = (t.first+ "\t").size();
            }
        }

        // now we have printed out every doc id of current word
        // if currSize < pageSize, this page is still not full, we have to make it "full" with padding "-"s
        // to make the index "easy" to read using of fseek
        string zeroStr = "-";
        unsigned int zeroSize = zeroStr.size();
        while (currSize < pageSize - 1) {
            outfile << "-";
            currSize += zeroSize;
        }
        outfile << endl;
    }
    // cerr << endl;
    helperIndex.close();
    outfile.close();
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    cout << "starts computation at " << ctime(&start_time) << endl;
    time_t end_time = chrono::system_clock::to_time_t(end);
    cout << "finished computation at " << ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";

}

void buildIndex_discarded(const string& textFile, const string& indexFile, unsigned int pageSize){
    // cout << textFile << indexFile << pageSize << endl;
    // create new index file use fstream to open a file for reading and writing:
    fstream indexFileStream;
    indexFileStream.open(indexFile, ios_base::app | ios_base::out );

    // create read stream
    ifstream dataFile(textFile);
    string thisLine; // in data file (one document)

    unordered_map<string, unsigned long> hashVal_LineNum; // hash_bitPos[hashVal] = location (line#) in the outer index
    // process data file line by line
    unsigned long currentDocID = -1; // first being 0
    while (getline(dataFile, thisLine)) {
        currentDocID++;
        // cout << "\n" << thisLine << "\n";
        vector<string> parsedLineEle = Split(thisLine);
        // for (vector<string>::iterator i = parsedLineEle.begin(); i != parsedLineEle.end(); i++) {
        //     cout << *i << "|";
        // }
        // cout << endl;
        vector<string>::iterator i_vec = parsedLineEle.begin();
        i_vec++; // this is DOCXXX
        for (; i_vec != parsedLineEle.end(); i_vec++) {

            unordered_map<string, unsigned long>::iterator i_map = hashVal_LineNum.find(*i_vec);

            if (i_map == hashVal_LineNum.end()) {
                // new word
                hashVal_LineNum.insert(make_pair(*i_vec, currentDocID));
                // no need to check overflow, add new line in index file
                indexFileStream << *i_vec << "\t" << currentDocID << "\n";

            } else {
                // alreay existed
                // unsigned long lineNum = hashVal_LineNum.find();


            }
        }

    }
}
