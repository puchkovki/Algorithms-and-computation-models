all:
	g++ -std=c++17 -lstdc++  main.cpp Graph.cpp Vertex.cpp -o graph
asan:
	g++ -fsanitize=address,leak,undefined main.cpp Graph.cpp Vertex.cpp -o graph
run:
	./graph.out
