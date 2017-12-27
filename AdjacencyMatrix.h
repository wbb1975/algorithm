#ifndef ADJACENCYMATRIX_H_
#define ADJACENCYMATRIX_H_

#include <vector>

namespace wangbb
{
    class AdjacencyMatrix
    {
    protected:
	    int  n;
	    bool **a;
    public:
	    AdjacencyMatrix(int n0) : n(n0)
        {
	        a = new bool*[n];
	        for (int i = 0; i < n; i++)
	        {
		        a[i] = new bool[n];
		    }
	        for (int i = 0; i < n; i++)
	        {
		        for (int j = 0; j < n; j++)
		        {
			        a[i][j] = false;
			    }
	        }
        }
        virtual ~AdjacencyMatrix()
        {
	        for (int i = 0; i < n; i++)
	        {
		        delete[] a[i];
		    }
	        delete[] a;
        }
	    
	    void addEdge(int i, int j)
	    {
		    a[i][j] = true;
	    }
	    void removeEdge(int i, int j)
	    {
		    a[i][j] = false;
	    }
	    bool hasEdge(int i, int j)
	    {
		    return a[i][j];
	    }

	    void outEdges(int i, std::vector<int> &edges)
	    {
		    for (int j = 0; j < n; j++)
		    {
			    if (a[i][j])
			    {
			        edges.add(j);
			    }
			}
	    }
	    void inEdges(int i, std::vector<int> &edges)
	    {
		    for (int j = 0; j < n; j++)
		    {
			    if (a[j][i])
			    {
			        edges.add(j);
			    }
			}
	    }
	    int nVertices()
	    {
		    return n;
	    }
    };

}
#endif /* ADJACENCYMATRIX_H_ */
