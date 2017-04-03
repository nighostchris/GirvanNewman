#include <iostream>
#include <fstream>
#include "graph.h"

using namespace std;

int main(){
	int cluster = 1;	// record no. of clusters
	int firstcreate = 0;	// record the no. of decomposition
	ifstream ifs("input.txt");
	int graphsize = 0;
	ifs >> graphsize;
	Graph GN(graphsize);
	for (int i = 0; i < graphsize; i++) // input the matrix from input.txt
	{
		for (int j = 0; j < graphsize; j++)
		{
			int temp = 0;
			ifs >> temp;
			GN.edgeAdd(i, j, temp);
		}
	}
	const int twom = GN.totalEdge(); // set twom as totalEdge of first Matrix
	double** MM = new double*[graphsize]; // MM store Modularity Matrix
	for (int i = 0; i < graphsize; i++)
		MM[i] = new double[graphsize];
	for (int i = 0; i < graphsize; i++) // Modularity Matrix Computation
		for (int j = 0; j < graphsize; j++)
			MM[i][j] = GN.getNodeContent(i+1, j+1)-(GN.getNodeDegrees(i+1)*GN.getNodeDegrees(j+1)/(double)twom);
	GN.edge_bness_cal();
	Graph** store = new Graph*[1];
	while (GN.giveClusters() > cluster || GN.giveClusters() < graphsize) // compute all decomposition and store up the matrix
	{
		if (firstcreate == 0)
		{
			Graph* update = new Graph(GN);
			store[0] = update;
			cluster = GN.giveClusters();
			firstcreate++;
			GN.edge_bness_cal();
		}
		else
		{
			firstcreate++;
			Graph** update = new Graph*[firstcreate];
			for (int i = 0; i < firstcreate-1; i++)
				update[i] = store[i];
			update[firstcreate-1] = new Graph(GN);
			delete [] store;
			store = update;
			cluster = GN.giveClusters();
			GN.edge_bness_cal();
		}
	}
	ofstream myfile("output.txt");
	myfile << "Network Decomposition:\n";
	myfile.close();
	for (int i = 0; i < firstcreate; i++) // write network decomposition to output.txt
		store[i]->print();
	double check = 0;
	int optimal = 0;
	for (int i = 0; i < firstcreate; i++) // write modularity of graph to output.txt
	{
		double temp = store[i]->modularity_cal(twom, MM);
		if (temp > check)
		{
			check = temp;
			optimal = i;
		}
	}
	ifs.close();
	ofstream opt("output.txt", fstream::app);
	opt << "Optimal Structure: ";
	opt.close();
	store[optimal]->print();  // output optimal network decomposition
	for (int i = 0; i < graphsize; i++)
		delete [] MM[i];
	for (int i = 0; i < firstcreate; i++)
		delete store[i];
	delete store;
	delete [] MM;
	return 0;
}
