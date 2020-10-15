#include "Graph.h"

using namespace std;

int main()
{
    Graph graph("data.txt");
    Graph mst(graph.getNodeNumber());
    int total_weight;

    graph.kruskal(mst, total_weight);

    cout << total_weight << endl;

	return 0;
}
