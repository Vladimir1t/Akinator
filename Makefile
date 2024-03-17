All: tree
	tree.exe file_output.txt

tree: src\main.cpp src\tree.cpp stack\src\stack.cpp
	g++ -o tree src\main.cpp src\tree.cpp stack\src\stack.cpp


