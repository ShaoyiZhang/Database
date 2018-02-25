#ifndef FILE_H_
#define FILE_H_

/* A class for file operations
  An instance of this class will include:
  1. file name
  2. offset of the target
  
  This class also contain some class methods to help retrieve actual records from
  the file given a target word. These method will take 
*/

class FileOperation {

};

class FilePointer {
public:
  FilePointer( const char *filename, long int offset );
  FilePointer( string filename, long int offset );
private:
  const char * filename; // the filename filed will be the same for all words in our project
                         // however, it will be still useful for generic usage
  long int offset;
};

#endif