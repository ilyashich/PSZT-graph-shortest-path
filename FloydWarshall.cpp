/*
    Illia Yatskevich
    Paweł Maśluch
*/

/*
	Undirected graph !!!
	Non-negative weights !!!
	Input vertices numbered from 1 (but in program from 0) !!!
*/

#include<vector>
#include <fstream>
#include "benchmark.h"


using namespace std;


typedef long long LL;


const LL MAX_VERT = 1000; // maximum number of vertices

const LL INF = (LL) 1000000099 * 1000000009; // INFINITY

//const LL UNDEF = -1; // UNDEFINED


LL VERTEX_NUMBER; // number of vertices
LL EDGES_NUMBER; // number of edges

LL weights[MAX_VERT][MAX_VERT]; // matrix of weights; T[u][v] = T[v][u] = weight between u and v
LL shortest[MAX_VERT][MAX_VERT]; // matrix of lengths of shortest paths

void initDataStructures()
{

    for(LL u=0; u<=MAX_VERT - 1; ++u)
    {
        for(LL v=0; v<=MAX_VERT - 1; ++v)
        {
            weights[u][v] = INF;
            shortest[u][v] = INF;
            //last[u][v] = UNDEF;
        }
        shortest[u][u] = 0;
    }
}


void input(fstream& file)
{

    file >> VERTEX_NUMBER >> EDGES_NUMBER;

    LL u, v, weight;

    for(LL i=0; i<=EDGES_NUMBER - 1; ++i)
    {

        file >> u >> v >> weight;

        --u;
        --v;

        weights[u][v] = weights[v][u] = min(weight, weights[u][v]);

        shortest[u][v] = shortest[v][u] = min(shortest[u][v], weights[u][v]);
    }
}


void FloydWarshall()
{

    for(LL k=0; k<=VERTEX_NUMBER - 1; ++k)
    {
        for(LL u=0; u<=VERTEX_NUMBER - 1; ++u)
        {
            for(LL v=0; v<=VERTEX_NUMBER - 1; ++v)
            {
                if (shortest[u][v] > shortest[u][k] + shortest[k][v])
                {
                    shortest[u][v] = shortest[u][k] + shortest[k][v];

                }
            }
        }
    }
}


void compute()
{
    FloydWarshall();
}


void output()
{
    cout << endl;

    for(LL u=0; u<=VERTEX_NUMBER - 1; ++u)
    {
		for(LL v=0; v<=VERTEX_NUMBER - 1; ++v)
        {
            if (shortest[u][v] == INF)
            {
                cout << "INF ";
            }
            else
            {
                cout << shortest[u][v] << "\t";
            }
        }
        cout << endl << endl;;
    }
    cout << endl;
}


int solve(fstream& file)
{

    initDataStructures();

    input(file);
    
    //measuring time needed to compute
    Benchmark<std::chrono::microseconds> benchmark;
    compute();
    LL result = benchmark.elapsed();

    // Comment if graph is big
        output();
    
    return result;
}


int main()
{
    fstream file("graph.txt", ios::in);
    int floyd_warshall_time = solve(file);
    cout << "Floyd-Warshall time: " << floyd_warshall_time << endl;

    return 0;
}


/*

Testy:

Test #1:
4
5
1 2 5
2 4 4
4 3 6
3 2 12
1 4 11

Test #2:
In:
6 7
1 2 3
2 3 1
2 4 1
2 5 4
3 6 11
4 5 1
5 6 7
Out:
0 3 4 4 5 12
3 0 1 1 2 9
4 1 0 2 3 10
4 1 2 0 1 8
5 2 3 1 0 7
12 9 10 8 7 0


Test #3:



*/
