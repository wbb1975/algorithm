#ifndef ADJACENCYLISTS_H_
#define ADJACENCYLISTS_H_

#include <set>

namespace wangbb
{
    class AdjacencyLists
    {
    protected:
	    int n;
	    std::set<int> *adj;
    
    public:
	    AdjacencyLists(int n0)
	    {
	        n = n0;
	        adj = new set::set<int>[n];
	    }
	    virtual ~AdjacencyLists()
	    {
	        delete [] adj;
	    }
	    
	    void addEdge(int i, int j)
	    {
		    adj[i].add(j);
	    }

	    bool hasEdge(int i, int j)
	    {
		    return adj[i].contains(j);
	    }

		void inEdges(int i, std::set<int> &edges)
		{
		    for (int j = 0; j < n; j++)
		    {
			    if (adj[j].contains(i))
			    {
			        edges.insert(j);
			    }
			}
	    }

	    int nVertices()
	    {
		    return n;
	    }

	    void outEdges(int i, std::set<int> &edges)
	    {
		    for (auto it = adj[i].begin(); it != adj[i].end(); ++it)
		    {
			    edges.add(*it);
			}
	    }

	    void removeEdge(int i, int j)
	    {
		    if (adj[i].contains(j))
		    {
		        adj[i].erase(j);
		    }
	    }
    };
}
#endif /* ADJACENCYLISTS_H_ */
