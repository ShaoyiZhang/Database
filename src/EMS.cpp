//
// Created by Zhancheng Qian on 2018/3/10.
//

//#include "Sort.h"

// C++ program to implement external sorting using
// merge sort
#include <cstdlib>
//#include <bits/stdc++.h>
#include <cstdio>
#include <ctime>
#include <climits>
#include <fstream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include "EMS.h"

using namespace std;

extern int MAX;
extern int MAX_BUFFER;
extern int numRows;

struct MinHeapNode {
    // The element to be stored
    struct IndexRecord element;

    // index of the array from which the element is taken
    int i;
};

void pN (struct MinHeapNode mh);

// Prototype of a utility function to swap two min heap nodes
void swap(MinHeapNode *x, MinHeapNode *y);

// A class for Min Heap
class MinHeap {
    MinHeapNode *harr; // pointer to array of elements in heap
    int heap_size;     // size of min heap
    int capacity = 20000;

public:
    // Constructor: creates a min heap of given size
    MinHeap(MinHeapNode a[], int size);

    // to heapify a subtree with root at given index
    void MinHeapify(int);

    int parent(int i) { return (i-1)/2; }
    // to get index of left child of node at index i
    int left(int i) { return (2 * i + 1); }

    // to get index of right child of node at index i
    int right(int i) { return (2 * i + 2); }

    // to get the root
    MinHeapNode getMin() { return harr[0]; }

    // to replace root with new node x and heapify()
    // new root
    void replaceMin(MinHeapNode x) {
//        if (strcmp(x.element.word.c_str(), "") == 0)
//            printf("replace with: MAX\n");
//                else
//            printf("replace with: %s\n", x.element.word.c_str());
////        printf("this MinHeapNode x's size: %d\n", x.element.vec.size());
        harr[0] = x;
////        printf("this harrp[0]'s size: %d\n", harr[0].element.vec.size());
        MinHeapify(0);
//        printf("after replaceMin: \n");
        this->print();
    }

    void print(){
//        printf("\n-------------------------------------------\n");
//        printf("printing min heap: \n");
        for (int i =0; i<heap_size; i++ ){
//            if (strcmp (harr[i].element.word.c_str(), "") != 0)
//                printf("%s ", harr[i].element.word.c_str());
//                    else
//                printf("MAX ");
        }
//        printf("\n");
//        printf("-------------------------------------------\n\n");
    }

    void insertKey(MinHeapNode k);
};

// Constructor: Builds a heap from a given array a[]
// of given size
MinHeap::MinHeap(MinHeapNode a[], int size) {
    heap_size = 0;
    harr = a; // store address of array

    for (int j=0; j<size; j++) {
        insertKey(a[j]);
////        printf("\nheap after inserting: %d\n", a[j].element.hash);
        this->print();
////        printf("\n");
    }

//    this->print();
}

void MinHeap::insertKey(MinHeapNode k)
{
//    if (strcmp(k.element.word.c_str(), "") == 0)
//        printf("inserting: MAX\n");
//            else
//        printf("inserting: %s\n", k.element.word.c_str());

    if (heap_size == capacity)
    {
//        printf("\nOverflow: Could not insertKey\n");
        return;
    }

    // First insert the new key at the end
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;

    // Fix the min heap property if it is violated
//    while (i != 0 && (harr[parent(i)].element.word > harr[i].element.word))
//    {
////        printf("this needs to be swapped...........i: %d, \n", i);
////        printf("because I think %s is bigger than %s, \n", harr[parent(i)].element.word.c_str(), harr[i].element.word.c_str());
//        swap(&harr[i], &harr[parent(i)]);
//        i = parent(i);
//    }
    while (i != 0)
    {   if (harr[parent(i)].element.word > harr[i].element.word) {
//            printf("FIRST this needs to be swapped...........i: %d, \n", i);
//            printf("because I think i: %s is bigger than %s, \n", harr[i].element.word.c_str(), harr[parent(i)].element.word.c_str());
            swap(&harr[i], &harr[parent(i)]);
            i = parent(i);
        }
        else if (harr[left(parent(i))].element.word > harr[i].element.word && left(parent(i)) != i){
//            printf("SECOND this needs to be swapped...........i: %d, \n", i);
//            printf("because I think i: %s is bigger than %s, \n", harr[i].element.word.c_str(), harr[left(parent(i))].element.word.c_str());
            swap(&harr[i], &harr[left(parent(i))]);
            i = left(parent(i));
        }
        else {
            i = 0;
        }
    }
}

// A recursive method to heapify a subtree with root
// at given index. This method assumes that the
// subtrees are already heapified
void MinHeap::MinHeapify(int i) {
    int l = left(i);
    int r = right(i);

//    printf("+++++++++++\n");
    if (i < heap_size) {
//        if (strcmp(harr[i].element.word.c_str(), "") != 0)
//            printf("i: %s\n", harr[i].element.word.c_str());
//                else
//            printf("i: MAX\n");
    }
    if (l < heap_size) {
//        if (strcmp(harr[l].element.word.c_str(), "") != 0)
//            printf("l: %s\n", harr[l].element.word.c_str());
//                else
//            printf("l: MAX\n");
    }
    if (r < heap_size) {
//        if (strcmp(harr[r].element.word.c_str(), "") != 0)
//            printf("r: %s\n", harr[r].element.word.c_str());
//                else
//            printf("r: MAX\n");
    }
//    printf("+++++++++++\n");


    int smallest = i;
    int flag1 = 0, flag2 = 0;
    if (l < heap_size) {
        if (strcmp (harr[i].element.word.c_str(), "") == 0) {
//            printf("1st condition\n");
            smallest = l;
            flag1 = 1;
        }
        if (strcmp (harr[l].element.word.c_str(), "") != 0
            && harr[l].element.word < harr[i].element.word && flag1 == 0) {
//            printf("2nd condition\n");
            smallest = l;
        }
    }
    if (r < heap_size) {
        if (strcmp (harr[smallest].element.word.c_str(), "")  == 0) {
//            printf("3rd condition\n");
            smallest = r;
            flag2 = 1;
        }
        if(strcmp (harr[r].element.word.c_str(), "") != 0
           && harr[r].element.word < harr[smallest].element.word && flag2 == 0) {
//            printf("4th condition\n");
            smallest = r;
        }
    }
    // special condition
    if (l < heap_size && r < heap_size
        && strcmp (harr[i].element.word.c_str(), "") != 0
        && strcmp (harr[l].element.word.c_str(), "") == 0
        && strcmp (harr[r].element.word.c_str(), "")  == 0) {
//        printf("5th condition\n");
        smallest = i;
    }

    if (l < heap_size && r < heap_size
        && strcmp (harr[i].element.word.c_str(), "") == 0
        && strcmp (harr[l].element.word.c_str(), "") != 0
        && strcmp (harr[r].element.word.c_str(), "")  == 0) {
//        printf("6th condition\n");
        smallest = l;
    }

    if (l < heap_size && r < heap_size
        && strcmp (harr[i].element.word.c_str(), "") == 0
        && strcmp (harr[l].element.word.c_str(), "") == 0
        && strcmp (harr[r].element.word.c_str(), "")  != 0) {
//        printf("7th condition\n");
        smallest = r;
    }

    if (l < heap_size && r >= heap_size
        && strcmp (harr[i].element.word.c_str(), "") != 0
        && strcmp (harr[l].element.word.c_str(), "") == 0) {
//        printf("9th condition\n");
        smallest = i;
    }
    if (l < heap_size && r >= heap_size
        && strcmp (harr[i].element.word.c_str(), "") == 0
        && strcmp (harr[l].element.word.c_str(), "") != 0) {
//        printf("10th condition\n");
        smallest = l;
    }

    if (l >= heap_size && r < heap_size
        && strcmp (harr[i].element.word.c_str(), "") != 0
        && strcmp (harr[r].element.word.c_str(), "") == 0) {
//        printf("11th condition\n");
        smallest = i;
    }
    if (l >= heap_size && r < heap_size
        && strcmp (harr[i].element.word.c_str(), "") == 0
        && strcmp (harr[r].element.word.c_str(), "") != 0) {
//        printf("12th condition\n");
        smallest = r;
    }

    if (smallest != i) {
        this->print();
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }
}

// A utility function to swap two elements
void swap(MinHeapNode *x, MinHeapNode *y) {
    string a, b;
    if (strcmp (x->element.word.c_str(), "") == 0)
        a = "MAX";
    else
        a = x->element.word.c_str();
    if (strcmp (y->element.word.c_str(), "") == 0)
        b = "MAX";
    else
        b = y->element.word.c_str();
//    printf("swapping %s and %s\n", a.c_str(), b.c_str());
    MinHeapNode temp = *x;
////    printf("temp is good\n");
    *x = *y;
////    printf("x=y is good\n");
    *y = temp;
////    printf("y=x is good\n");
////    printf("swap is good\n");
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(struct IndexRecord arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    struct IndexRecord L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i].word <= R[j].word)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
        arr[k++] = L[i++];

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
        arr[k++] = R[j++];
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(struct IndexRecord arr[], int l, int r) {
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

FILE *openFile(char *fileName, char *mode) {
    FILE *fp = fopen(fileName, mode);
    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    return fp;
}

// Merges k sorted files.  Names of files are assumed
// to be 1, 2, 3, ... k
void mergeFiles(char *output_file, int n, int k) {
    ifstream in[k];
    for (int i = 0; i < k; i++) {
        char fileName[10];

        // convert i to string
        snprintf(fileName, sizeof(fileName), "%d", i);

        // Open output files in read mode.
        in[i].open(fileName);
    }
//    printf("arrive 1\n");
    // FINAL OUTPUT FILE
    FILE *out = openFile(output_file, "w");
//    printf("arrive 2\n");
    // Create a min heap with k heap nodes.  Every heap node
    // has first element of scratch output file
    MinHeapNode *harr = new MinHeapNode[k];
    int i;
    for (i = 0; i < k; i++) {
        // break if no output file is empty and
        // index i will be no. of input files
//        printf("this is: %d\n", i);
        string line;
        if (!getline(in[i], line))
        {
            break;
        }
//        printf("the line is %s\n", line.c_str());
        vector<string> tokens;
        vector<unsigned long> tmp_vec;
        boost::split(tokens, line, boost::is_any_of("\t"));
        harr[i].element.word = tokens[0];
        for (int w = 1; w < tokens.size(); w++){
//            printf("%s\n", tokens[w].c_str());
            tmp_vec.push_back(stol(tokens[w]));
        }
        harr[i].element.vec = tmp_vec;

        harr[i].i = i;
    }

    MinHeap hp(harr, i); // Create the heap

    int count = 0;
    int rowNum = 1;
    int stats[k];
    for (int u = 0; u<k; u++)
        stats[u]=0;

    struct MinHeapNode prev;
    struct MinHeapNode curr;
    // Now one by one get the minimum element from min
    // heap and replace it with next element.
    // run till all filled input files reach EOF
    while (count != i) {
        // Get the minimum element and store it in output file
        MinHeapNode root = hp.getMin();
////        printf("root has size: %d\n", root.element.vec.size());
        string s = root.element.word + "\t";
        std::vector<unsigned long>::iterator it;
        int a = 0;
        for (it = root.element.vec.begin(); it != root.element.vec.end(); ++it) {
            if (a != root.element.vec.size() - 1)
                s = s + to_string(*it) + "\t";
            else
                s = s + to_string(*it) + "\n";
            a++;
        }
        fprintf(out, "%s", s.c_str());

//        fprintf(out, "%d\t%d\t%d\t%s\n", root.element.hash, root.element.prev,
//                root.element.next, root.element.filePointer.c_str());
//        printf("getting out: ");
//        if (strcmp (root.element.word.c_str(), "") == 0)
//            printf("ROOT EMPTY !!!!!!!!!!!!!!!!!!!!!\n");
//                else
//            printf("%s\n", root.element.word.c_str());
////        printf("outputting: %d\n", rowNum++);
        // Find the next element that will replace current
        // root of heap. The next element belongs to same
        // input file as the current min element.
        int flag = 0;
        string line;
        if (!getline(in[root.i], line)) {
            vector<unsigned long> vec; vec.push_back(0);
            struct IndexRecord ir = {"", vec};
            root.element = ir;
//            printf("count is done!!!\n");
            count++;
            flag = 1;
        }
////        printf("so now I am reading: %s\n", line.c_str());
        if (flag == 0){
            vector<string> tokens;
            vector<unsigned long> tmp_vec;
            boost::split(tokens, line, boost::is_any_of("\t"));
            root.element.word = tokens[0];
            for (int w = 1; w < tokens.size(); w++)
                tmp_vec.push_back(stol(tokens[w]));
            root.element.vec = tmp_vec;
//            stats[root.i]++;
//            printf("size: %d\n", tokens.size());
            rowNum++;
        }

////        printf("replace with: \n");
//        pR(root.element);
        // Replace root with next element of input file
        hp.replaceMin(root);
    }

    // close input and output files
    for (int i = 0; i < k; i++)
        in[i].close();

    fclose(out);
}

// Using a merge-sort algorithm, create the initial runs
// and divide them evenly among the output files
void createInitialRuns(char *input_file, int run_size,
                       int num_ways) {
    // For big input file
    ifstream in (input_file);

    // output scratch files
    FILE *out[num_ways];
    char fileName[10];
    for (int i = 0; i < num_ways; i++) {
        // convert i to string
        snprintf(fileName, sizeof(fileName), "%d", i);

        // Open output files in write mode.
        out[i] = openFile(fileName, "w");
    }

    // allocate a dynamic array large enough
    // to accommodate runs of size run_size
    auto *arr = (struct IndexRecord *) malloc(run_size * sizeof(struct IndexRecord));

    bool more_input = true;
    int next_output_file = 0;

    // read first row metadata
    string line;

    int i;
    while (more_input) {
        // write run_size elements into arr from input file
        for (i = 0; i < run_size; i++)
        {
//            printf("i is: %d\n", i);
            if (!getline(in, line))
            {
//                printf("break\n");
                more_input = false;
                break;
            }
            vector<std::string> tokens;
            vector<unsigned long> tmp_vec;
            boost::split(tokens, line, boost::is_any_of("\t"));
            arr[i].word = tokens[0];
            for (int k = 1; k < tokens.size(); k++)
                tmp_vec.push_back(stol(tokens[k]));

            arr[i].vec = tmp_vec;
        }
        // sort array using merge sort
        mergeSort(arr, 0, i - 1);
        // write the records to the appropriate scratch output file
        // can't assume that the loop runs to run_size
        // since the last run's length may be less than run_size
        for (int j = 0; j < i; j++) {
//            printf("j is: %d\n", j);
            string s = arr[j].word + "\t";
            std::vector<unsigned long>::iterator it;
            int k = 0;
            for (it = arr[j].vec.begin(); it != arr[j].vec.end(); ++it) {
                if (k != arr[j].vec.size() - 1)
                    s = s + to_string(*it) + "\t";
                else
                    s = s + to_string(*it) + "\n";
                k++;
            }
            fprintf(out[next_output_file], "%s", s.c_str());
////            printf("cstr: %s\n", arr[j].filePointer.c_str());
        }

        next_output_file++;
    }

    // close input and output files
    for (int i = 0; i < num_ways; i++)
        fclose(out[i]);

    free(arr);
    in.close();
}

// For sorting data stored on disk
void externalSort(char *input_file, char *output_file, int num_ways, int run_size) {
    // read the input file, create the initial runs,
    // and assign the runs to the scratch output files
    createInitialRuns(input_file, run_size, num_ways);
//    printf("here1111\n");

    // Merge the runs using the K-way merging
    mergeFiles(output_file, run_size, num_ways);
//    printf("here2222\n");
}

void sortDocIds(char *index_file, char *input_file, char *output_file){
    ifstream ix (index_file);
}


// Driver program to test above
//int main() {
//    int totalWords; //50000
//    int B = MAX_BUFFER; //20
//
//    char input_1[] = "head.txt";
//    char input_2[] = "tail.txt";
//    char output_1[] = "head_1.txt";
//    char output_2[] = "tail_1.txt";
//
//    ifstream tf, tf2;
//    tf.open(input_1);
//    tf2.open(input_2);
//    FILE *out1 = openFile(output_1, "w");
//    FILE *out2 = openFile(output_2, "w");
//
//    static const char * alphanum[] = {
//            "1\t2\t3\n",
//            "1\t2\t3\t4\t5\n",
//            "1\t2\t3\t4\t5\t6\t7\n"};
//
//    // generate input
//    string l;
//    for (int i = 0; i < 1000; i++) {
//        getline(tf, l);
////        printf("i: %d\n", i);
////        printf("l: %s\n", l.c_str());
////        char tmp[10]; gen_random(tmp, 10);
//        fprintf(out1, "%s\t", l.c_str());
//        fprintf(out1, "%s", alphanum[0]);
//    }
//    for (int i = 0; i < 1000; i++) {
//        getline(tf2, l);
////        printf("i: %d\n", i);
////        printf("l: %s\n", l.c_str());
////        char tmp[10]; gen_random(tmp, 10);
//        fprintf(out2, "%s\t", l.c_str());
//        fprintf(out2, "%s", alphanum[0]);
//    }
////    for (int i = 0; i < totalWords/2; i++) {
////        char tmp[10]; gen_random(tmp, 10);
////        fprintf(in, "%s\t", tmp);
////        fprintf(in, "%s", alphanum[rand() % 3]);
////        fprintf(in, "%s\t", tmp);
////        fprintf(in, "%s", alphanum[rand() % 3]);
////    }
//
//    fclose(out1);
//    fclose(out2);
//    tf.close();
//    tf2.close();
//
//    mergeTwoFiles(output_1, output_2, "output.txt");
//
//    return 0;
//}

void setBufferSize(int size){
    MAX_BUFFER = size;
}

void mergeTwoFiles(const char *input_1, const char *input_2, const char *output_file) {
    int totalWords; //50000
    int B = MAX_BUFFER; //20

    char input_file[] = "input.txt";

    FILE *in = openFile(input_file, "w");

    ifstream in1, in2;
    in1.open(input_1);
    in2.open(input_2);
    string row;
    int count = 0;
    while(getline(in1, row)){
        fprintf(in, "%s\n", row.c_str());
        count ++;
    }
    while(getline(in2, row)){
        fprintf(in, "%s\n", row.c_str());
        count ++;
    }

    totalWords = count;

    // No. of Partitions of input file.
    int num_ways;

    // The size of each partition
    int run_size;
    // The size of last partition

    if (totalWords % B == 0){
        num_ways = totalWords / B;
        run_size = B;
    } else {
        num_ways = totalWords / B + 1;
        run_size = B;
    }

    fclose(in);
    in1.close();
    in2.close();

    externalSort(input_file, const_cast<char *>(output_file), num_ways, run_size);

}

void gen_random(char *s, const int len) {
    static const char alphanum[] =
            "0123456789"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}
//void pR (struct IndexRecord ir){
////    printf("\n");
////    printf("{\n");
////    printf("hash: %d, pr: %d, nx: %d, fp: %s\n", ir.hash, ir.prev, ir.next, ir.filePointer.c_str());
////    printf("}\n");
////    printf("\n");
//}
//
//void pN (struct MinHeapNode mh){
////    printf("\n");
////    printf("{\n");
////    printf("mh i: %d\n", mh.i);
////    printf("hash: %d, pr: %d, nx: %d, fp: %s\n", mh.element.hash, mh.element.prev, mh.element.next, mh.element.filePointer.c_str());
////    printf("}\n");
////    printf("\n");
//}