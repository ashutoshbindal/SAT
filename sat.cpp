#include<iostream>
using namespace std;

int main()
{
	int vertices,edges,K;
	int M[vertices][K],E[vertices][vertices];

	for (int i = 0; i < vertices; ++i)
	{
		for (int j=0; j<K; j++)
		{
			E[i][j]=0;
		}
	}

	int a,b;
	for(int i=0; i < edges; i++)
	{
		cin>>a>>b;
		E[a][b]=1;
		E[b][a]=1;
	}

	//clause 1: every vertex should be present in atleast one of the K subgraphs
	int terms=1;
	for (int i = 0; i < vertices; ++i)
	{
		for (int j=0; j < K ; j++)
		{
			cout<<terms++<<" ";
		}
		cout<<0<<endl;
	}

	//clause 2: every edge should be present in atleast one of the K subgraphs
	for (int i = 0; i < vertices; ++i)
	{
		for (int j=i; j<K; j++)  // traverse only upper half of matrix
		{
			if ( E[i][j] )
			{

			}
		}
	}
}
