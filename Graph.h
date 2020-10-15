/*--------------------------------------------------------------------------
    Undirected graph class (with adjacency matrix representation)
--------------------------------------------------------------------------*/

#ifndef GRAPH_H
#define GRAPH_H

using namespace std;
#include <vector>
#include <string>
#include <iostream>


//For a random graph: default value range for edges
const int DEFAULT_VALUE_MIN = 1;
const int DEFAULT_VALUE_MAX = 10;

class Graph
{
    private:
        /*----------------------------------------------------
                Adjacency matrix with matrix[x][y] = v
            v=0 ==> no edge from x to y
            v>0 ==> edge from x to y with value v
        ----------------------------------------------------*/
        vector<vector<int>> matrix;
        int edge_num;
        int node_num;

    public:
        Graph(int size=0, float density=0.0, int value_min=DEFAULT_VALUE_MIN, int value_max=DEFAULT_VALUE_MAX);
        Graph(string file_name);

        int getNodeNumber() const;
        int getEdgeNumber() const;
        bool adjacent(int x, int y) const;
        vector<int> nodes() const;
        vector<tuple<int,int,int>> edges() const;
        vector<int> neighbors(int x) const;
        void addEdge(int x, int y, int v);
        void deleteEdge(int x, int y);
        int getEdgeValue(int x, int y) const;

        void kruskal(Graph& mst, int& total_weight) const;

        virtual ~Graph();
};

#endif // GRAPH_H
