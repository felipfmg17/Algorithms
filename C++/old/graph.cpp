#include <bits/stdc++.h>
#define f(x,n) for(int x=0;x<n;x++)

using namespace std;



typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<long long > vl;
typedef vector<ii> vii;



int main(){
	return 0;
}





#define G_SIZE 1000000


struct Graph{
	int nodes;
	vector< vi > connections(G_SIZE, vi() );
	vector< vi > weights(G_SIZE,vi() );
	set< int > reps;
	vi out_degrees(G_SIZE,0);





	vb reach(int u){
		vb vis(nodes,false);
		vi st;	st.push_back(u);

		while(!st.empty()){
			u=st.pop_back();
			f(i,connections[u].size()){
				int v=connections[u][i];
				if(!vis[v]) st.push_back(v);
				vis[v]=true;
			}	
		}
	}
};




