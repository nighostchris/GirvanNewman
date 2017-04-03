#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <list>
#include "queue.h"
#include "stack.h"

using namespace std;

class Graph
{
	private:
		int nodes;
		int** edge;	// store matrix of graph

	public:
		Graph(int no_of_nodes); // constructor of a graph for given no of nodes
		Graph(const Graph& g);
		~Graph();	// destructor of a graph

		void edgeAdd(int start, int end, int value); // input the edge into the graph
		void edge_bness_cal(); // calculate betweenness of edges in a graph
		void DFS(int i, bool visited[]) const;
		void DFS_print(int i, bool visited[], list <int>& printing) const;
		void print() const;
		double modularity_cal(int twom, double** MM) const;

		bool checkConnect(int start, int end) const; // check if the given 2 nodes are connected
		int getNodeContent(int start, int end) const; // return value of particular node
		int giveClusters() const; // return how many connected components in the graph
		int getNodeDegrees(int node_no) const; // return degrees of nodes
		int checkSameCluster(int start, int end) const; // check if 2 nodes are in same clusters
		int totalEdge() const; // return the total edge of that matrix
};

#endif
