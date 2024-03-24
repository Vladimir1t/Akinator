All: tree
	tree.exe file_output.txt
	dot -Tpng graphviz\graph.dot -o graphviz\tree_graph.png
	start graphviz\tree_graph.png

tree: src\main.cpp src\tree.cpp stack\src\stack.cpp
	g++ -o tree src\main.cpp src\tree.cpp stack\src\stack.cpp


