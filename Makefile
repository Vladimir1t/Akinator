all: tree
	tree.exe file_output.txt
	dot -Tpng graphviz\graph.dot -o graphviz\tree_graph.png
	start graphviz\tree_graph.png

tree: src\main.cpp src\tree.cpp src\akinator.cpp src\input_output.cpp stack\src\stack.cpp stack\src\stack_path.cpp
	g++ -o tree src\main.cpp src\tree.cpp stack\src\stack.cpp stack\src\stack_path.cpp src\akinator.cpp src\input_output.cpp


