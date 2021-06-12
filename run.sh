#!/bin/bash
g++ Astar.cpp benchmark.h -Wall -std=c++11 -o Astar
g++ Dijkstra.cpp benchmark.h -Wall -std=c++11 -o Dijkstra
g++ FloydWarshall.cpp benchmark.h -Wall -std=c++11 -o FloydWarshall
echo ----------------------
echo Astar
./Astar
echo ----------------------
echo $'\n'
echo ----------------------
echo Dijkstra
./Dijkstra
echo ----------------------
echo $'\n'
echo ----------------------
echo FloydWarshall
./FloydWarshall
echo ----------------------