#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>

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

int main(){
    //variable declaration
    int n, e, k;
    vector<pair<int, int>> edge;

    //reading from the file
    ifstream fin;
    fin.open("test.graph");
    fin>>n>>e>>k;

    //checking
    // cout<<n<<" "<<e<<" "<<k<<endl;

    while(!fin.eof()){
        int a, b;
        fin>>a>>b;
        //start the indexing from 0
        // a -= 1;
        // b -= 1;
        // cout<<a<<" "<<b<<endl;
        pair<int, int> temp;
        temp = {a, b};
        edge.push_back(temp);
    }
    fin.close();

    //remove the last element since it is read twice
    edge.pop_back();

    //just checking the vector
    // for(int i=0; i<edge.size(); i++)
    // {
    //     cout<<edge[i].first<<" "<<edge[i].second<<endl;
    // }

    //literal
    int m[n][k];

    for(int i=0; i<n; i++){
        for(int j=0; j<k; j++){
            m[i][j] = 0;
        }
    }

    //writing into a filename
    ofstream fout;
    fout.open("input.txt", std::ios_base::app);
    fout<<"p cnf # #\n";

    int thresh = 0;
    int count = 0;

    //clause 1: all nodes be present in atleast one subgraph
    for(int i=0; i<n; i++){
        for(int j=0; j<k; j++){
            fout<<to_string(i*k + j+1)<<" ";
        }
        fout<<"0\n";
    }
    thresh = n*k;

    //initialize for clause 3
    int temp_edge[n][n];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            temp_edge[i][j] = 0;
        }
    }

    //clause 2
    count = thresh + 1;
    for(int i=0; i<edge.size(); i++){
        count = (n+i)*k + 1;
        for(int j=0; j<k; j++){
            fout<<to_string(count)<<" ";
            count++;
        }
        fout<<"0\n";
        count = (n+i)*k + 1;

        int first_node = edge[i].first;
        int second_node = edge[i].second;

        //updating for clause 3
        temp_edge[first_node-1][second_node-1] = 1;
        temp_edge[second_node-1][first_node-1] = 1;

        for(int j=0; j<k; j++){
            fout<<"-"<<to_string(count)<<" "<<to_string((first_node-1)*k + j+1)<<" 0\n";
            fout<<"-"<<to_string(count)<<" "<<to_string((second_node-1)*k + j+1)<<" 0\n";
            count++;
        }
    }
    thresh = (n*k) + (edge.size()*k);

    //clause 3
    //setting all the edges appropritately
    count = 1;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(temp_edge[i][j] == 1){
                fout<<to_string(thresh+count)<<" 0\n";
            }
            else{
                fout<<"-"<<to_string(thresh+count)<<" 0\n";
            }
            count++;
        }
    }
    //writing the clause
    for(int z=1; z<=k; z++){
        //iterating over all the combination of edges
        for(int i=0; i<n; i++){
            for(int j=i+1; j<n; j++){
                fout<<"-"<<to_string(i*k + z)<<" -"<<to_string(j*k + z)<<" "<<to_string(thresh + (i*n) + j + 1)<<" 0\n";
            }
        }
    }
    thresh += (n*n);

    //clause 4
    for(int i=0; i<k; i++){
        for(int j=0; j<k; j++){
            if(i == j){
                continue;
            }
            else{
                //writing the n-extra literals
                for(int z=1; z<=n; z++){
                    fout<<to_string(thresh + z)<<" ";
                }
                fout<<"0\n";

                //writing the clauses
                for(int z=1; z<=n; z++){
                    fout<<"-"<<to_string(thresh+z)<<" "<<to_string((z-1)*k + i+1)<<" 0\n";
                    fout<<"-"<<to_string(thresh+z)<<" -"<<to_string((z-1)*k + j+1)<<" 0\n";
                }

                thresh += n;
            }
        }
    }

    fout.close();

    //minisat call
    system("./MiniSat_v1.14_linux input.txt output.txt");

    //reading form the output file
    string str;
    ifstream fin;
    fin.open("output.txt");
    getline(fin, str);

    if(str == "SAT"){
        while(getline(fin, str)){
            //process the satisfiability
            vector<string> temp;
            split(str, " ", temp);
            temp.pop_back();

            //translating the output into matrix
            int iter = 0;
            for(int i=0; i<n; i++){
                for(int j=0; j<k; j++){
                    string temp_literal = temp[iter];
                    int lit = stoi(temp_literal);
                    if(lit > 0){
                        m[i][j] = 1;
                    }

                    iter++;
                }
            }
            //conditional
            break;
        }

        //writing in the output file
        fout.open("answer.txt", std::ios_base::app);
        for(int i=1; i<=k; i++){
            int node_exist = 0;
            for(int j=0; j<n; j++){
                if(m[j][i-1] == 1){
                    node_exist++;
                }
            }
            fout<<"#"<<to_string(i)<<" "<<to_string(node_exist)<<"\n";
            bool flag = false;
            for(int j=0; j<n; j++){
                if(m[j][i-1] == 1){
                    if(flag){
                        fout<<to_string(j+1);
                    }
                    else{
                        fout<<" "<<to_string(j+1);
                    }
                }
            }
            fout<<"\n\n"<<endl;
        }
        fout.close();
    }
    else{
        fout.open("answer.txt", std::ios_base::app);
        fout<<"0\n";
        fout.close();
    }

    fin.close();
}
