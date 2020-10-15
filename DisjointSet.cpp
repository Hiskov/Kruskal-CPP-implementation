#include "DisjointSet.h"




DisjointSet::DisjointSet(vector<int> const &element)
{
    MakeSet(element);
}


/*------------------------------------------
    Construct a set with only singletons
--------------------------------------------*/
void DisjointSet::MakeSet(vector<int> const &element)
{
    for (int i : element)
        parent[i] = i;  //each element has no parents
}


/*------------------------------------------------
    Find the root of the tree that contains x
--------------------------------------------------*/
int DisjointSet::Find(int x)
{
  if (parent[x] == x) // if x is the root
     return x;
  return Find(parent[x]);   //we ascend until we find the root
}


/*------------------------------------------------
    Do the union of two subset x and y
--------------------------------------------------*/
void DisjointSet::Union(int x, int y)
{
    int x_root = Find(x);
    int y_root = Find(y);
    if(x_root != y_root)    //if they are not the the same tree/subset
        parent[x] = y;
}



//no particular destructor
DisjointSet::~DisjointSet()
{

}
