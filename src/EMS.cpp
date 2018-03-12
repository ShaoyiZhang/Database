//
// Created by Zhancheng Qian on 2018/3/10.
//

#include "EMS.h"
#include "Sort.h"

// C++ program to implement external sorting using
// merge sort
#include <cstdlib>
//#include <bits/stdc++.h>
#include <cstdio>
#include <ctime>
#include <climits>
#include <fstream>

using namespace std;

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
        harr[0] = x;
        MinHeapify(0);
        printf("after replaceMin: \n");
        this->print();
    }

    void print(){
        printf("printing min heap: \n");
        for (int i =0; i<heap_size; i++ )
            printf("%d ", harr[i].element.hash);
        printf("\n");
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
        printf("\nheap after inserting: %d\n", a[j].element.hash);
        this->print();
        printf("\n");
    }

    this->print();
}

void MinHeap::insertKey(MinHeapNode k)
{
    if (heap_size == capacity)
    {
        printf("\nOverflow: Could not insertKey\n");
        return;
    }

    // First insert the new key at the end
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;
    printf("inserting: %d\n", k.element.hash);
    // Fix the min heap property if it is violated
    while (i != 0 && (harr[parent(i)].element.hash > harr[i].element.hash))
    { printf("this needs to be swapped...........i: %d, \n", i);
        printf("because I think %d is bigger than %d, \n", harr[parent(i)].element.hash, harr[i].element.hash);
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

// A recursive method to heapify a subtree with root
// at given index. This method assumes that the
// subtrees are already heapified
void MinHeap::MinHeapify(int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;
//    printf("PREEE i: %d, l: %d, r: %d, small: %d\n", i,l, r, smallest);
//    printf("11111111\n");
    if (l < heap_size && harr[l].element.hash < harr[i].element.hash) {
//        printf("2222222\n");
        smallest = l;
    }
//    printf("666666\n");
    if (r < heap_size && harr[r].element.hash < harr[smallest].element.hash) {
//        printf("3333333\n");
        smallest = r;
    }
//    printf("777777\n");
//    printf("AFTTT i: %d, l: %d, r: %d, small: %d\n", i,l, r, smallest);
    if (smallest != i) {
//        printf("4444444\n");
        swap(&harr[i], &harr[smallest]);
//        printf("done swap\n");
        MinHeapify(smallest);
    }
//    printf("5555555\n");
}

// A utility function to swap two elements
void swap(MinHeapNode *x, MinHeapNode *y) {
    printf("swapping %d and %d\n", x->element.hash, y->element.hash);
    MinHeapNode temp = *x;
//    printf("temp is good\n");
    *x = *y;
//    printf("x=y is good\n");
    *y = temp;
//    printf("y=x is good\n");
//    printf("swap is good\n");
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
        if (L[i].hash <= R[j].hash)
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
    FILE *in[k];
    for (int i = 0; i < k; i++) {
        char fileName[10];

        // convert i to string
        snprintf(fileName, sizeof(fileName), "%d", i);

        // Open output files in read mode.
        in[i] = openFile(fileName, "r");
    }

    // FINAL OUTPUT FILE
    FILE *out = openFile(output_file, "w");

    // Create a min heap with k heap nodes.  Every heap node
    // has first element of scratch output file
    MinHeapNode *harr = new MinHeapNode[k];
    int i;
    for (i = 0; i < k; i++) {
        // break if no output file is empty and
        // index i will be no. of input files
        if (fscanf(in[i], "%d\t", &harr[i].element.hash) != 1)
            break;
        char ccc[100];
        fscanf(in[i], "%d\t", &harr[i].element.prev);
        fscanf(in[i], "%d\t", &harr[i].element.next);
        fscanf(in[i], "%s\n", ccc); harr[i].element.filePointer = ccc;

        harr[i].i = i; // Index of scratch output file
    }
    printf("i is: %d\n", i);

//    for (int k=0; k<i; k++){
//        pN(harr[k]);
//    }

    MinHeap hp(harr, i); // Create the heap

    int count = 0;
    int cc = 0;
    int stats[k];
    for (int u = 0; u<k; u++)
        stats[u]=0;
    // Now one by one get the minimum element from min
    // heap and replace it with next element.
    // run till all filled input files reach EOF
    while (count != i) {
        // Get the minimum element and store it in output file
        MinHeapNode root = hp.getMin();
        fprintf(out, "%d\t%d\t%d\t%s\n", root.element.hash, root.element.prev,
                root.element.next, root.element.filePointer.c_str());
        printf("getting out: \n");
        pR(root.element);

//        printf("outputting: %d\n", cc++);
        // Find the next element that will replace current
        // root of heap. The next element belongs to same
        // input file as the current min element.
        int flag = 0;
        if (fscanf(in[root.i], "%d\t", &root.element.hash) != 1) {
            struct IndexRecord ir = {SIZE_MAX, 0000, 1111, ""};
            root.element = ir;
            printf("break at %d, file %d\n", cc, root.i);
            printf("printing stats: \n");
            for (int l=0; l<k; l++){
                printf("%d ", stats[root.i]);
            }
            printf("\n");
            hp.print();
            count++;
            flag = 1;
        }
        if (flag == 0){
            char ccc[100];
            fscanf(in[root.i], "%d\t", &root.element.prev);
            fscanf(in[root.i], "%d\t", &root.element.next);
            fscanf(in[root.i], "%s\n", ccc); root.element.filePointer = ccc;
            stats[root.i]++;
            cc++;
        }

        printf("replace with: \n");
        pR(root.element);
        // Replace root with next element of input file
        hp.replaceMin(root);
    }

    // close input and output files
    for (int i = 0; i < k; i++)
        fclose(in[i]);

    fclose(out);
}

// Using a merge-sort algorithm, create the initial runs
// and divide them evenly among the output files
void createInitialRuns(char *input_file, int run_size,
                       int num_ways) {
    // For big input file
    FILE *in = openFile(input_file, "r");

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

    int i;
    while (more_input) {
        // write run_size elements into arr from input file
        for (i = 0; i < run_size; i++)
        {
            printf("i is: %d\n", i);
            if (fscanf(in, "%d\t", &arr[i].hash) != 1)
            {
//                printf("break\n");
                more_input = false;
                break;
            }
            char ccc[100];
            fscanf(in, "%d\t", &arr[i].prev);
            fscanf(in, "%d\t", &arr[i].next);
            fscanf(in, "%s", ccc); arr[i].filePointer = ccc;
//            printf("hash: %d\n", arr[i].hash);
//            printf("hash: %d\n", arr[i].prev);
//            printf("hash: %d\n", arr[i].next);
            printf("cstr: %s\n", arr[i].filePointer.c_str());
        }

        // sort array using merge sort
//        printf("before merge\n");
        mergeSort(arr, 0, i - 1);
//        printf("after merge\n");
//        printf("i is %d\n", i);
//        printf("runsize is %d\n", run_size);

        // write the records to the appropriate scratch output file
        // can't assume that the loop runs to run_size
        // since the last run's length may be less than run_size
        for (int j = 0; j < i; j++) {
            fprintf(out[next_output_file], "%d\t%d\t%d\t%s\n", arr[j].hash, arr[j].prev,
                    arr[j].next, arr[j].filePointer.c_str());
//            printf("cstr: %s\n", arr[j].filePointer.c_str());
        }

        next_output_file++;
    }

    // close input and output files
    for (int i = 0; i < num_ways; i++)
        fclose(out[i]);

    free(arr);
    fclose(in);
}

// For sorting data stored on disk
void externalSort(char *input_file, char *output_file, int num_ways, int run_size) {
    // read the input file, create the initial runs,
    // and assign the runs to the scratch output files
    createInitialRuns(input_file, run_size, num_ways);

    // Merge the runs using the K-way merging
    mergeFiles(output_file, run_size, num_ways);
}


// Driver program to test above
int main() {
    int totalWords = 70000; //50000
    int B = 20; //20

    // No. of Partitions of input file.
    int num_ways = B;

    // The size of each partition
    int run_size;
    // The size of last partition
    int last_size;

    if (totalWords % num_ways == 0) {
        run_size = totalWords / num_ways;
//        last_size = 0;
    } else {
        run_size = totalWords / num_ways + 1;
//        last_size = totalWords - (run_size * (num_ways - 1));
    }

    char input_file[] = "input.txt";
    char output_file[] = "output.txt";

    FILE *in = openFile(input_file, "w");

    srand(time(NULL));

    int max_number = 65536;
    int minimum_number = 0;

    // generate input
    for (int i = 0; i < num_ways * run_size; i++)
        fprintf(in, "%d\t%d\t%d\t%s\n", rand() % (max_number + 1 - minimum_number) + minimum_number,
                0000, 1111, "12345678");

    fclose(in);


    externalSort(input_file, output_file, num_ways, run_size);

    return 0;
}

void pR (struct IndexRecord ir){
    printf("\n");
    printf("{\n");
    printf("hash: %d, pr: %d, nx: %d, fp: %s\n", ir.hash, ir.prev, ir.next, ir.filePointer.c_str());
    printf("}\n");
    printf("\n");
}

void pN (struct MinHeapNode mh){
    printf("\n");
    printf("{\n");
    printf("mh i: %d\n", mh.i);
    printf("hash: %d, pr: %d, nx: %d, fp: %s\n", mh.element.hash, mh.element.prev, mh.element.next, mh.element.filePointer.c_str());
    printf("}\n");
    printf("\n");
}