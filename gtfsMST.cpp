#include<bits/stdc++.h>
#include <fstream>
#include <string>
using namespace std;
bool comp(const vector<int>& a, const vector<int>& b) {
    return a[2] < b[2]; 
}

int findPar(int u, vector<int> &parent) {
    if(parent[u] != u){
        parent[u] = findPar(parent[u],parent);
    }
    return parent[u];
}

void unionn(int u, int v, vector<int> &parent, vector<int> &rank) {
    u = findPar(u, parent);
    v = findPar(v, parent);
    if(rank[u] < rank[v]) {
    	parent[u] = v;
    }
    else if(rank[v] < rank[u]) {
    	parent[v] = u; 
    }
    else {
    	parent[v] = u;
    	rank[u]++; 
    }
}

string findvertex(string str, int i)
{
    vector<string> v;
    stringstream ss(str);
    while (ss.good()) 
    {
        string substr;
        getline(ss, substr, ',');
        v.push_back(substr);
    }
    return v[i];
}
int main ()
{
    vector<string> lines;
    string line;
    string filename("stop_times.txt");
    ifstream input_file2(filename);
    while (getline(input_file2, line)){
        lines.push_back(line);
    }

    int u,v,w,wo,wi;
    srand((unsigned) time(NULL));
    u = stoi(findvertex(lines[1],3));
    int maxVertex = u;
    wo=(int)stof(findvertex(lines[1],8));
    vector<vector<int>> edges;

    for (unsigned int i = 2; i < lines.size(); ++i)
    {
        v=stoi(findvertex(lines[i],3));
        maxVertex = max(maxVertex,v);
        wi=(int)stof(findvertex(lines[i],8));
        w=abs(wi-wo);
        edges.push_back({u,v,w});
        u=v;
    }
    sort(edges.begin(), edges.end(), comp);  

	vector<int> parent(maxVertex + 1);
	for(int i = 0 ; i <= maxVertex ; i++) parent[i] = i; 
 
	vector<int> rank(maxVertex + 1, 0); 
	
	int cost = 0;
	vector<vector<int>> mst; 
	for(auto &it : edges) {
	    if(findPar(it[1], parent) != findPar(it[0], parent)) {
	        cost += it[2]; 
	        mst.push_back({it[0], it[1],it[2]}); 
	        unionn(it[0], it[1], parent, rank); 
	    }
       
	}
    
    vector<string> stops;
    string stop;
    ifstream input_file("stops.txt");
    while (getline(input_file, stop)){
        stops.push_back(stop);
    }

    unordered_map<int,string> stopIdtoName;
    for(int i = 1 ; i < stops.size() ; i++){
        int stopId = stoi(findvertex(stops[i],0));
        string stopName = findvertex(stops[i],2);
        stopIdtoName[stopId] = stopName;
    }

    cout << cost << endl;
	for(auto& it : mst) cout << stopIdtoName[it[0]] << " - " << stopIdtoName[it[1]] << " " << it[2] << endl; 
	return 0;

}