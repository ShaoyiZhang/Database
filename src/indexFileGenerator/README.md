# index file generator

***
## Structure

- Two layers:

    - outer layer (one file on disk):
    ```
            hash(word_i)    FilePointer
               0            filePtr0
               1            filePtr1
               2            filePtr2
    ```
    where FilePointer is ( file name, offset, numOfDupKey ), so each FilePointer is "pointing" to a page of the secondary layer:

    - secondary layer (multiple files on disk):

        - each file is essentially a "page", which consist the **binary** form of:   
        ```        
                (hashvalue, docList, prevPage, nextPage)
        ```


***
## Classes

- WordFPtrPair
  - it is in the form of:
 ```
        hash(word0) | FilePointer
```
- OuterLayer

- PageOfIndex

- SecondaryLayer

***
## Dependencies

- It borrows FilePointer from file.h, ...
