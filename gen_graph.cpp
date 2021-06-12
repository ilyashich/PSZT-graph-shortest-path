#include <iostream>
#include <random>
#include <fstream>


using namespace std;

int main(int argc, char *argv[])
{
    fstream file("graph.txt", ios::out);

    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> distribution(1,25);

    float vert = atoi(argv[1]);
    int edges = (int)(vert * ((vert-1)/2));
    file << vert << ' ' << edges << endl;
    for(int i = 1; i <= (int)vert; ++i)
    {
        for(int j = i+1; j <= (int)vert; ++j)
        {
            file << i << ' ' << ' ' << j << ' ' << distribution(generator) << endl;
        }
    }

    return 0;
}