#!/bin/bash
g++ gen_graph.cpp -Wall -o generator
g++ Astar.cpp benchmark.h -Wall -std=c++11 -o Astar
g++ Dijkstra.cpp benchmark.h -Wall -std=c++11 -o Dijkstra
g++ FloydWarshall.cpp benchmark.h -Wall -std=c++11 -o FloydWarshall

./generator 5
echo ----------------------
echo Vertex = 5
./Astar
./Dijkstra
./FloydWarshall
echo ----------------------
./generator 15
echo ----------------------
echo Vertex = 15
./Astar
./Dijkstra
./FloydWarshall
echo ----------------------    

for i in {10..140..10}
do
    ./generator $i
    echo ----------------------
    echo Vertex = $i
    ./Astar
    ./Dijkstra
    ./FloydWarshall
    echo ----------------------
done