/*
    Illia Yatskevich
    Paweł Maśluch
*/

#include <queue>
#include <vector>
#include <fstream>
#include "benchmark.h"


using namespace std;


typedef long long LL;

typedef pair<LL, LL> PLL;

typedef vector<PLL> VPLL;

typedef priority_queue<PLL> PQPLL;


const LL MAX_VERT = 1000; // max number of vertices in our graph

const LL INF = (LL) 1000000099 * 1000000009; // INFINITY


/* Graph data structures */
LL VERTEX_NUMBER; // number of vertices
LL EDGES_NUMBER; // number of edges
VPLL graph[MAX_VERT]; // gragh; edge has a form (weight, endVertex)

/* Heuristic function data structures */
LL minNumberofEdges[MAX_VERT]; // minNumberOfEdges[u] - minimum number of edges from a given vertex "startVertex" to vertex "u"
LL minCostOfEdge = INF; // min cost of edge in all the graph

/* Astar data structures */
LL best[MAX_VERT][MAX_VERT]; // best[u][v] - the shortest path from vertex "u" to vertex "v"


void inputData(fstream& file)
{

    file >> VERTEX_NUMBER >> EDGES_NUMBER;

    LL u, v, weight;

    for(LL i = 0; i <= EDGES_NUMBER-1; ++i)
    {

        file >> u >> v >> weight;

        --u;
        --v;

        minCostOfEdge = min(minCostOfEdge, weight);

        graph[u].push_back(make_pair(weight, v));
        graph[v].push_back(make_pair(weight, u));
    }
}


void BFS(LL startVertex)
{

    bool visited[VERTEX_NUMBER];

    for(LL i = 0; i <= VERTEX_NUMBER-1; ++i)
    {
        minNumberofEdges[i] = INF;
        visited[i] = false;
    }
    minNumberofEdges[startVertex] = 0;

    queue<LL> Q;
    Q.push(startVertex);

    LL u, v, r;

    while (!Q.empty())
    {

        u = Q.front();
        Q.pop();

        if (!visited[u])
        {

            r = graph[u].size();

            for(LL i = 0; i <= r-1; ++i)
            {

                v = graph[u][i].second;

                if (minNumberofEdges[u] + 1 < minNumberofEdges[v])
                {

                    minNumberofEdges[v] = minNumberofEdges[u] + 1;

                    Q.push(v);
                }
            }

            visited[u] = true;
        }
    }
}


/* Heuristic function for a given vertex "u". */
LL h(LL u)
{
    return minCostOfEdge * minNumberofEdges[u];
}


void Astar(LL startVertex, LL endVertex)
{

    PQPLL PQ;
    LL g_score[VERTEX_NUMBER]; // g[u] - length of shortest path from "startVertex" to "u"
    bool visited[VERTEX_NUMBER]; // visited[u] = true if "u" was explored in our algorithm, false otherwise

    for(LL i = 0; i <= VERTEX_NUMBER-1; ++i)
    {
        g_score[i] = INF;
        visited[i] = false;
    }
    g_score[startVertex] = 0;

    PQ.push(make_pair(-(g_score[startVertex] + h(startVertex)), startVertex));

    LL u, r, v, weight;
    while (!PQ.empty())
    {

        u = PQ.top().second;
        PQ.pop();

        if (u == endVertex)
        {
            best[startVertex][endVertex] = g_score[u];
            return;
        }

        if (!visited[u])
        { // if "u" wasn't explored

            r = graph[u].size();

            for(LL i = 0; i <= r-1; ++i)
            {

                weight = graph[u][i].first;
                v = graph[u][i].second;

                if (g_score[v] > g_score[u] + weight)
                {
                    g_score[v] = g_score[u] + weight;

                    PQ.push(make_pair(-(g_score[v] + h(v)), v));
                }
            }

            visited[u] = true;
        }
    }
}


void AstarAllPairs()
{

    /* Initialization of Astar data structures. */
    for(LL u = 0; u <= VERTEX_NUMBER-1; ++u)
    {

        for(LL v = 0; v <= VERTEX_NUMBER-1; ++v)
        {
            best[u][v] = INF;
        }

        best[u][u] = 0;
    }

    /* Astar for each pair of nodes. */
    for(LL endVertex = 0; endVertex <= VERTEX_NUMBER-1; ++endVertex)
    {

        BFS(endVertex); // we find shortest paths (in number of edges) from endVertex to rest of vertices

        for(LL startVertex = 0; startVertex <= VERTEX_NUMBER-1; ++startVertex)
        {
            Astar(startVertex, endVertex);
        }
    }
}


void compute()
{

    AstarAllPairs();
}


void output()
{

    cout << endl;

    for(LL u = 0; u <= VERTEX_NUMBER-1; ++u)
    {

        for(LL v = 0; v <= VERTEX_NUMBER-1; ++v)
        {
            if (best[u][v] == INF)
            {
                cout << "INF ";
            }
            else
            {
                cout << best[u][v] << "\t";
            }
        }
        cout << endl << endl;
    }
    cout << endl;
}


int solve(fstream& file)
{

    inputData(file);

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
    int astar_time = solve(file);
    cout << "A* time: " << astar_time << endl;

    return 0;
}

/*

Testy

Test #1:
4 5
1 2 5
1 4 11
2 3 12
2 4 4
3 4 6


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
3 3
1 2 10
2 3 6
3 1 40


Test #4:
1 0





*/
