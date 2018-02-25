# Database

Our project will contain the following C++ classes:

- TreeNode class
  - A node in the BPlus Tree that can be either internal node or leaf node depending on the isLeaf field.
- B Plus Tree class
  - Supporting B Plus tree operations
- FileOperation class
  - Wrapper class for various C style file operations
- FilePointer class
  - A small class containing index info for a target word.
  - Will be used in the leafnode of the B Plus tree
- Console class
  - A while loop console reads in and parse commands
- Index class
  - Performs the inital index building procedure on a large text file
