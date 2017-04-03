#include <fstream>
#include "graph.h"

Graph::Graph(int no_of_nodes) : nodes(no_of_nodes)
{
	edge = new int*[nodes];
	for (int i = 0; i < nodes; i++)
		edge[i] = new int[nodes];
	for (int i = 0; i < nodes; i++)
		for (int j = 0; j < nodes; j++)
			edge[i][j] = 0;
}

Graph::Graph(const Graph& g)
{
	nodes = g.nodes;
	edge = new int*[nodes];
	for (int i = 0; i < nodes; i++)
		edge[i] = new int[nodes];
	for (int i = 0; i < nodes; i++)
		for (int j = 0; j < nodes; j++)
			edge[i][j] = g.edge[i][j];
}

Graph::~Graph()
{
	for (int i = 0; i < nodes; i++)
		delete [] edge[i];
	delete [] edge;
}

void Graph::edgeAdd(int start, int end, int value)
{
	edge[start][end] = value;
	edge[end][start] = value;
}

void Graph::edge_bness_cal()
{
	double b_map[nodes][nodes]; // store betweenness of all existing edges
	for (int i = 0; i < nodes; i++)
		for (int j = 0; j < nodes; j++)
			b_map[i][j] = 0;	// initialize the betweenness as 0

	for (int n = 1; n <= nodes; n++) // loop for n times, which n is no. of nodes in the graph
	{
		Queue Q;	// initialize empty queue
		Stack S(nodes);  // initialize empty stack
		list <int> parents[nodes]; // initialize array of linked list for storing parent node of nodes
		int* dfr = new int[nodes+1]; // distance from root for nodes
		int* shortest = new int[nodes+1]; // no. of shortest path passing through the node
		for (int i = 1; i <= nodes; i++) // initialize dfr and shortest array
		{
			dfr[i] = -1;
			shortest[i] = 0;
		}
		shortest[n] = 1;
		dfr[n] = 0; // set distance from root for first node as 0
		Q.enqueue(n); // put the first node in queue to start BFS

		while (Q.checkEmpty() == false)	// Find no. of shortest path passing each node
		{
			int node = Q.dequeue();
			S.push(node);
			for (int i = 1; i <= nodes; i++)
			{
				if (checkConnect(node, i) == true)  // check if 2 nodes connected
				{
					if (dfr[i] < 0)	// check if first time visit the node
					{
						Q.enqueue(i);
						dfr[i] = dfr[node]+1;
					}
					if (dfr[i] == dfr[node]+1) // check if it is shortest path
					{
						shortest[i] = shortest[i]+shortest[node];
						parents[i-1].push_back(node);
					}
				}
			}
		}

		double distribute[nodes]; // initialize cumulative flow at every nodes
		for (int i = 0; i < nodes; i++)
			distribute[i] = 0;

		while (S.checkEmpty() == false) // calculate betweenness of edges
		{
			int node = S.pop();	// get latest node from list
			list <int> temp = parents[node-1];
			for (list<int>::iterator i = temp.begin(); i != temp.end(); ++i) // loop through all parent nodes of node
			{
				double temp = ((double)shortest[*i]/shortest[node])*(1+distribute[node-1]);
				b_map[*i-1][node-1] += temp;
				b_map[node-1][*i-1] = b_map[*i-1][node-1];
				distribute[*i-1] += temp;
			}
		}
		delete [] dfr;
		delete [] shortest;
	}
	double max = 0;
	for (int i = 0; i < nodes; i++)
		for (int j = 0; j < nodes; j++)
		{
			if (b_map[i][j] > max)
				max = b_map[i][j];
		}
	for (int i = 0; i < nodes; i++)  // remove all edges with highest betweenness
		for (int j = 0; j < nodes; j++)
			if (b_map[i][j] == max)
			{
				edge[i][j] = 0;
				edge[j][i] = 0;
			}
}

bool Graph::checkConnect(int start, int end) const
{
	if (edge[start-1][end-1] == 1)
		return true;
	return false;
}

int Graph::giveClusters() const
{
	int count = 0;
	bool visited[nodes];
	for (int i = 0; i < nodes; i++)
		visited[i] = false;
	for (int i = 0; i < nodes; i++)
	{
		if (visited[i] == false)
		{
			visited[i] = true;
			count++;
			DFS(i, visited);
		}
	}
	return count;
}

void Graph::DFS(int i, bool visited[]) const
{
	for (int j = 0; j < nodes; j++)
		if (checkConnect(i+1, j+1) == true && visited[j] == false)
		{
			visited[j] = true;
			DFS(j, visited);
		}
}

void Graph::print() const
{
	ofstream myfile("output.txt", fstream::app);
	myfile << "(";
	bool visited[nodes];
	bool check = true;
	for (int i = 0; i < nodes; i++)
		visited[i] = false;
	for (int i = 0; i < nodes; i++)
	{
		list <int> printing;
		if (visited[i] == false)
		{
			visited[i] = true;
			printing.push_back(i+1);
			DFS_print(i, visited, printing);
		}
		printing.sort();
		for (list<int>::iterator i = printing.begin(); i != printing.end(); ++i)
		{
			if (printing.size() == 1)
			{
				myfile << "[" << *i << "]";
				for (int i = 0; i < nodes; i++)
				{
					if (visited[i] == false)
					{
						check = true;
						break;
					}
					else
						check = false;
				}
				if (check == true)
				{
					myfile << ", ";
					check = false;
				}
			}
			else if (i == printing.begin())
				myfile << "[" << *i;
			else if (i == --printing.end())
			{
				myfile << ", " << *i << "]";
				for (int i = 0; i < nodes; i++)
				{
					if (visited[i] == false)
					{
						check = true;
						break;
					}
					else
						check = false;
				}
				if (check == true)
				{
					myfile << ", ";
					check = false;
				}
			}
			else
				myfile << ", " << *i;
		}
	}
	myfile << ")\n";
	myfile.close();
}

void Graph::DFS_print(int i, bool visited[], list <int>& printing) const
{
	for (int j = 0; j < nodes; j++)
		if (checkConnect(i+1, j+1) == true && visited[j] == false)
		{
			visited[j] = true;
			printing.push_back(j+1);
			DFS_print(j, visited, printing);
		}
}

double Graph::modularity_cal(int twom, double** MM) const
{
	double modularity = 0;
	for (int i = 0; i < nodes; i++)
		for (int j = 0; j < nodes; j++)
			if (checkSameCluster(i+1, j+1) == 1)  // loop through all the edges in the current matrix to determine modularity
				modularity += MM[i][j];
	modularity /= twom;
	ofstream myfile("output.txt", fstream::app);
	myfile << giveClusters() << " clusters: modularity " << modularity << "\n";
	myfile.close();
	return modularity;
}

int Graph::getNodeDegrees(int node_no) const
{
	int count = 0;
	for (int i = 0; i < nodes; i++)
		if (edge[node_no-1][i] == 1)
			count++;
	return count;
}

int Graph::checkSameCluster(int start, int end) const
{
	int result = 0;
	bool visited[nodes];
	for (int i = 0; i < nodes; i++)
		visited[i] = false;
	visited[start-1] = true;
	DFS(start-1, visited);
	if (visited[end-1] == true)
		result = 1;
	return result;
}

int Graph::totalEdge() const
{
	int result = 0;
	for (int i = 1; i <= nodes; i++)
		result += getNodeDegrees(i);
	return result;
}

int Graph::getNodeContent(int start, int end) const
{
	return edge[start-1][end-1];
}
