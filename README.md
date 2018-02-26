# Database

Our project will contain the following C++ classes:

- B Plus Tree class
  - Supporting necessary B Plus tree operations
  - In the leaf node, each word will be map to a FilePointer object ( index file name, offset, numOfDupKey ).
    - Essentially, this is the <k, rid-list> approach and thus there will be no duplicate keys in the B Plus Tree
  - Depending on the insertion of keywords, overflow page might be created in the index file, but these overlow pages is transparent to th e B Plus Tree.
- TreeNode class
  - A small class representing nodes in the BPlus Tree
  - A node can be either internal node or leaf node depending on the isLeaf field
- FileOperation class
  - Wrapper class for various C style file operations
  - Might be merged to other classes in actual imlementation.
- FilePointer class
  - A small class containing index info for a target word
  - Will be used in the leaf node of the B Plus tree
- Console class
  - A while loop console reads in and parse commands as well as calling appropriate methods.
- Index class
  - Performs the inital index building procedure on a large text file
  - Mostly static methods
- Database class
  - The main class of the project, containing instances of the B Plus Tree class, Console class.
  - Rollback and Concurrency will be implemented here.
    - Current proposal is to use timestamp to implement rollback and concurrency.
  - After deleting a keyword, an index page might contain empty records. We will NOT remove this page since removing it will destory the index structre.
  
