#include "Graph.h"
#include <ctime>
#include <random>
#include <fstream>
#include <tuple>
#include <algorithm>    //sort
#include "DisjointSet.h"

//generate a random float between 0 and 1
inline float randomFloat(){return (rand() % 10)/10.0;}



/*----------------------------------------------------------------------
  Constructor with the size of the graph and the density (Random graph)
            with values between value_min and value_max
------------------------------------------------------------------------*/
Graph::Graph(int size, float density, int value_min, int value_max):
    edge_num(0),
    node_num(size)
{
    srand(time(0)); //seed init
    int value;  //value of the created edge
    matrix = vector<vector<int>>(size, vector<int>(size));
    for(int i = 0 ; i < size ; i++)
    {
        for(int j = i+1 ; j < size ; j++) //no directed edge ==> we treat half of the matrix
        {
            if(randomFloat() < density){
                value = value_min + value_max*randomFloat();
                addEdge(i, j, value);
                edge_num++;
            }
        }
    }
}


/*----------------------------------------------------------------------
       Constructs the graph with the data in the file "file_name"

  format:
        *first line: number of node
        *for the other lines: one line ==> one edge (i, j, value).
------------------------------------------------------------------------*/
Graph::Graph(string file_name):
    edge_num(0),
    node_num(0)
{
    ifstream file(file_name);   //file stream (read)
    int i, j; //current edge read
    int value;  //current value read

    if (!file.is_open()) {
        cout << "[ERROR] Failed to open " << file_name << endl;
        throw invalid_argument("Invalid file name");
    }

    file >> node_num;
    matrix = vector<vector<int>>(node_num, vector<int>(node_num));

    while(!file.eof()){ //one line per iteration
        file >> i;
        file >> j;
        file >> value;
        matrix[i][j] = value;

        edge_num++;
    }
}


/*-----------------------------------------------------
                Return the number of node
-------------------------------------------------------*/
int Graph::getNodeNumber() const
{
    return node_num;
}


/*-----------------------------------------------------
                Return the number of edge
-------------------------------------------------------*/
int Graph::getEdgeNumber() const
{
    return edge_num;
}


/*-----------------------------------------------------
 Tests whether there is an edge from node x to node y
-------------------------------------------------------*/
bool Graph::adjacent(int x, int y) const
{
    return matrix[x][y] > 0;    //0 ==> false, >0 ==> true
}


/*--------------------------------------------------------
            Lists all nodes of the graph
----------------------------------------------------------*/
vector<int> Graph::nodes() const
{
    vector<int> nodes(node_num);
    for(int i = 0 ; i < node_num ; i++)
    {
        nodes[i] = i;
    }
    return nodes;
}

/*--------------------------------------------------------
  Lists all edges (tuple) with their values (value, i, j)
----------------------------------------------------------*/
vector<tuple<int,int,int>> Graph::edges() const
{
    vector<tuple<int,int,int>> edges(node_num*node_num);
    for(int i = 0 ; i < node_num ; i++)
    {
        for(int j = 0 ; j < node_num ; j++)
        {
            if(adjacent(i, j)){
                edges.push_back(make_tuple(matrix[i][j], i, j));
            }
        }
    }
    return edges;
}


/*--------------------------------------------------------
 Lists all nodes y such that there is an edge from x to y
----------------------------------------------------------*/
vector<int> Graph::neighbors(int x) const
{
    vector<int> neigh;
    for(int y = 0 ; y < node_num ; y++)
    {
        if(matrix[x][y] > 0)//there is an edge from x to y
        {
            neigh.push_back(y); //we add y to the list
        }
    }
    return neigh;
}


/*--------------------------------------------------------
          Adds the edge from x to y with value v
----------------------------------------------------------*/
void Graph::addEdge(int x, int y, int v)
{
    matrix[x][y] = v;
    matrix[y][x] = v; //no directed edge ==> symmetric matrix
}


/*--------------------------------------------------------
               Removes the edge from x to y
----------------------------------------------------------*/
void Graph::deleteEdge(int x, int y)
{
    matrix[x][y] = 0;
}



/*--------------------------------------------------------
     Returns the value associated to the edge (x,y)
----------------------------------------------------------*/
int Graph::getEdgeValue(int x, int y) const
{
    return matrix[x][y];
}


/*--------------------------------------------------------
        Implementation of Kruskal algorithm.
    Returns a MST of the graph and his total weight.
----------------------------------------------------------*/
void Graph::kruskal(Graph& mst, int& total_weight) const
{
    DisjointSet ds(nodes());
    vector<tuple<int,int,int>> all_edges = edges();
    total_weight = 0;

    sort(all_edges.begin(), all_edges.end()); //Sort by 1st element of tuple (values of edges)

    for(auto it = all_edges.begin() ; it != all_edges.end(); ++it)   //for each edge in ascending order of values
    {
        int value = get<0>(*it);
        int i = get<1>(*it);
        int j = get<2>(*it);

        if(ds.Find(i) != ds.Find(j))
        {
            mst.addEdge(i, j, value);
            total_weight += value;
            ds.Union(i, j);
        }
    }
}



//no particular destructor
Graph::~Graph()
{

}
