#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void split(string str, string splitBy, vector<string>& tokens)
{
    tokens.push_back(str);
    size_t splitAt;
    size_t splitLen = splitBy.size();
    string frag;
    while(true)
    {
        frag = tokens.back();
        splitAt = frag.find(splitBy);
        if(splitAt == string::npos)
        {
            break;
        }
        tokens.back() = frag.substr(0, splitAt);
        tokens.push_back(frag.substr(splitAt+splitLen, frag.size()-(splitAt+splitLen)));
    }
}

int main()
{
    string str;
    ifstream fin;
    fin.open("output.txt");
    getline(fin, str);
    // cout<<str<<endl;
    ofstream fout;
    fout.open("answer.txt", std::ios_base::app);
    if(str == "SAT"){
        while(getline(fin, str)){
            // cout<<str<<endl;
            vector<string> temp;
            split(str, " ", temp);
            temp.pop_back();
            for(int i=0; i<temp.size(); i++){
                fout<<temp[i]<<"\n";
                cout<<stoi(temp[i])<<endl;
            }
        }
    }
    fout.close();
    fin.close();

	// int vertices,edges,K;
	// int M[vertices][K],E[vertices][vertices];
    //
	// for (int i = 0; i < vertices; ++i)
	// {
	// 	for (int j=0; j<K; j++)
	// 	{
	// 		E[i][j]=0;
	// 	}
	// }
    //
	// int a,b;
	// for(int i=0; i < edges; i++)
	// {
	// 	cin>>a>>b;
	// 	E[a][b]=1;
	// 	E[b][a]=1;
	// }
    //
	// //clause 1: every vertex should be present in atleast one of the K subgraphs
	// int terms=1;
	// for (int i = 0; i < vertices; ++i)
	// {
	// 	for (int j=0; j < K ; j++)
	// 	{
	// 		cout<<terms++<<" ";
	// 	}
	// 	cout<<0<<endl;
	// }
    //
	// //clause 2: every edge should be present in atleast one of the K subgraphs
	// for (int i = 0; i < vertices; ++i)
	// {
	// 	for (int j=i; j<K; j++)  // traverse only upper half of matrix
	// 	{
	// 		if ( E[i][j] )
	// 		{
    //
	// 		}
	// 	}
	// }
}
