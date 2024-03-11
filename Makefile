All: tree
	tree.exe

tree: src\main.cpp src\tree.cpp
	g++ -o tree src\main.cpp src\tree.cpp

