CXX=g++
#CXX=clang++

CXXFLAGS = -std=c++11 -Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field

# CXXFLAGS = -std=c++11 -Wall -Wextra -Werror

TESTS = test01
#test01

all: ${TESTS}

# main: Graph.o BPlusTree.o Main.o
# 	${CXX} $^ -o $@

#test01.o : File.cpp Node.cpp test01.cpp
test01: bPlusTree/File.o bPlusTree/Node.o bPlusTree/BPlusTree.o bPlusTree/test01.o
	${CXX} $^ -o $@

index: indexFileGenerator/indexGenerator.o
	${CXX} $^ -o $@
#tree: BTree.o Main.o TreeNode.o
#	${CXX} $^ -o $@

#test02: test02.o Student.o HashTable.o
#	${CXX} $^ -o $@

tests:${TESTS}
	./test01

LEAKTESTS=test01

leaktests: ${LEAKTESTS}

leaktest01: main
	- valgrind -q --dsymutil=yes --leak-check=full ./main

clean:
	/bin/rm -f ${TESTS} *.o
