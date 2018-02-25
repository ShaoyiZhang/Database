# Database

Our project will contain the following C++ classes:

- B Plus Tree class
  - Supporting necessary B Plus tree operations
- TreeNode class
  - A node in the BPlus Tree that can be either internal node or leaf node depending on the isLeaf field
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
