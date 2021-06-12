/*
    Illia Yatskevich
    Paweł Maśluch
*/

/*
	Undirected graph !!!
	Non-negative weights !!!
	Input vertices numbered from 1 (but in program from 0) !!!
*/
#include <vector>
#include <queue>
#include <fstream>
#include "benchmark.h"


using namespace std;


typedef long long LL;

typedef pair<LL, LL> PLL;

typedef vector<PLL> VPLL; // a structure of graph

typedef priority_queue<PLL> PQPLL; // priority queue


const LL MAX_VERT = 1000; // maximum number of vertices

const LL INF = (LL) 1000000099 * 1000000009; // INFINITY

const LL UNDEF = -1; // UNDEFINED


LL VERTEX_NUMBER; // number of vertices
LL EDGES_NUMBER; // number of edges

VPLL graph[MAX_VERT]; // graph; each edge has a form (weight, endVertex)
LL shortest[MAX_VERT][MAX_VERT]; // shortest[u][v] - length of shortest path from "u" to "v"
LL last[MAX_VERT][MAX_VERT]; // last[u][v] - last (before "v") vertex on a shortest path from "u" to "v"


void input(fstream& file)
{

    file >> VERTEX_NUMBER >> EDGES_NUMBER;

    LL u, v, weight;

    for(LL i=0; i<=EDGES_NUMBER - 1; ++i)
    {

        file >> u >> v >> weight;

        --u;
        --v;

        graph[v].push_back(make_pair(weight, u));
        graph[u].push_back(make_pair(weight, v));
    }
}


void Dijkstra(LL startVertex)
{

    /* Initialization of data structures */
    bool visited[VERTEX_NUMBER]; // visited[v] = true if a vertex "v" is already explored in our algorithm; false otherwise

    for(LL v=0; v<=VERTEX_NUMBER - 1; ++v)
    {
        shortest[startVertex][v] = INF;
        last[startVertex][v] = UNDEF;
        visited[v] = false;
    }
    shortest[startVertex][startVertex] = 0;


    /* Priority queue */
    PQPLL PQ;
    PQ.push(make_pair(-shortest[startVertex][startVertex], startVertex));


    /* Let's start Dijkstra! */
    LL u, numberOfNeighbours, v, w;

    while (!PQ.empty())
    {

        u = PQ.top().second;
        PQ.pop();

        if (!visited[u])
        {

            numberOfNeighbours = graph[u].size();

            for(LL i=0; i<=numberOfNeighbours - 1; ++i)
            {
                v = graph[u][i].second;
                w = graph[u][i].first;

                if (shortest[startVertex][v] > shortest[startVertex][u] + w)
                {

                    shortest[startVertex][v] = shortest[startVertex][u] + w;
                    last[startVertex][v] = u;

                    PQ.push(make_pair(-shortest[startVertex][v], v));
                }
            }

            visited[u] = true;
        }
    }
}


void DijkstraAllStartVertices()
{

    for(LL startVertex=0; startVertex<=VERTEX_NUMBER - 1; ++startVertex)
    {
        Dijkstra(startVertex);
    }
}


void compute()
{
    DijkstraAllStartVertices();
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
        cout << endl << endl;
    }
    cout << endl;

}


int solve(fstream& file)
{

    input(file);

    //measuring time needed to compute
    Benchmark<std::chrono::microseconds> benchmark;
    compute();
    LL result = benchmark.elapsed();

    //Comment if graph is big
        output();
    
    return result;
}


int main()
{
    fstream file("graph.txt", ios::in);
    int dijkstra_time = solve(file);
    cout << "Dijkstra time: " << dijkstra_time << endl;

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
