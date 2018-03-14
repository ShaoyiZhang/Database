# index file generator

***
## Structure

- Two layers:

    - outer layer (one file on disk):
    ```
        line       content

          1         [metaData] (one line)
          2+        hash(word_i)    prev    next    FilePointer

    ```
    ```
          2          xxx             -1       5      filePtrA
          3          yyy             -1      -1      filePtrB
          4          zzz             -1      -1      filePtrC
          5          xxx              2      -1      filePtrD
    ```

        where FilePointer is ( file name, offset, numOfDupKey ), so each FilePointer is "pointing" to a page of the secondary layer

    - secondary layer (multiple files on disk):

        - each file is essentially a "page", which consists a list of document IDs



***
## Dependencies

- It borrows FilePointer from file.h, ...

## some useful codes

int tempVal = stoi(tempraryStr.substr(0, 8), nullptr, 2);
