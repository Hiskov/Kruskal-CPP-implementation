#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <map>
#include <vector>

using namespace std;

/*--------------------------------------------------------------------
            Disjoint-set data structure implementation
==> Used to manage a partition
----------------------------------------------------------------------*/

class DisjointSet
{
    private:
        /*-----------------------------------------------------------------------------------------------------
            We use a std::map to simulate the forest data structure usually used in Disjoint-set implementation

            * One tree of the forest = subset of the partition
            * If parent[x] = y ==> y is the parent of x in a tree of the forest (x and y are in the same subset)
        -------------------------------------------------------------------------------------------------------*/
        map<int,int> parent;

    public:
        DisjointSet(vector<int> const &element);

        //The three methods of the disjoint-set data structure
        void MakeSet(vector<int> const &element);
        int Find(int x);
        void Union(int x, int y);

        virtual ~DisjointSet();

};

#endif // DISJOINTSET_H
