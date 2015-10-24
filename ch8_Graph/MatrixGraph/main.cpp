//#include "MatrixGraph.h"
#include "ALGraph.h"

#include <fstream>
using namespace std;

int main(){
	cout<<"+------------------------------------------------------+"<<endl;
	cout<<"#1 Input and Output the graph "<<endl;
	ifstream fin("data.txt");
	assert(fin);
	ALGraph<char,int> g;
	fin >> g;
	cout << g;

	cout<<"output DFS:"<<endl;
	g.DFS();
	cout<<endl;

	cout<<"output BFS:"<<endl;
	g.BFS();
	cout << endl;

	cout<<"The Kruskal is:"<<endl;
	g.Kruskal();
	cout << endl;

	cout<<"The Prim is:"<<endl;
	g.Prim();
	cout << endl;
	
	cout<<"The Dijkstra is:"<<endl;
	Dijkstra(g, 0);
	cout << endl;

	cout<<"The Floyed is:"<<endl;
	Floyed(g);
	cout << endl;
	return 0;
}