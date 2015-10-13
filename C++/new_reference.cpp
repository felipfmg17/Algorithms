///////// NEW REFERENCE ///////

#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int ,int> ii;
typedef vector< ii > vii;




// Count Connected Components

int vis[1000000],cc;

void dfs(int u){
	vis[u]=1;
	for(int v:g[u])
		if(vis[v]==0)
			dfs(v);
}

cc=0;
fill(vis,vis+n,0);
for(int i=0;i<n;i++)
	if(vis[i]==0){
		dfs(u);
		cc++;
	}


// Single Source Shortest Path Unweighted Graph (BFS)


vi dist(n,-1);
for(int i;i<n;i++){
	if(dist[i]==-1){
		deque<int> order();
		order.push_back(i);
		dist[i]=0;
		while(!order.empty()){
			int u=order.front();
			order.pop_front();
			for(int v:g[u])
				if(dist[v]!=-1){
					dist[v]=dist[u]+1;
					order.push_back(v);
				}
		}
	}
}



// Topological Sort Kahn Algorithm

vi wait,order;	
for(int i=0;i<n;i++)		
	if(deg[i]==0)
		wait.push_back(i);	
while(!wait.empty()){
	int u=wait.back();
	wait.pop_back();
	order.push_back(u);
	for(int v:g[u]){
		deg[v]--;
		if(deg[v]==0)
			wait.push_back(v);
	}
}


// Find Cycle

vi state;

bool dfs(int u,int p){
	state[u]=GRAY;
	for(int v:g[u]){
		if(state[v]==WHITE)
			if(dfs(v,u))
				return true;
		else if(state[v]==GRAY && v!=p)
			return true;
	}
	state[u]=BLACK;
	return false;
}


state.assign(n,WHITE);
for(int i=0;i<n;i++)
	if(state==WHITE)
		dfs(i,-1);




// Bipartite Check (Bicoloring)


int color[1000000];

bool dfs(int u,int c){
	color[u]=c;
	for(int v:g[u])
		if(color[v]==-1)
			if(!dfs(v,c^1))	return false;
		else if(color[v]==color[u])	return false;	
	return true;
}

fill(color,color+n,-1);
for(int i=0;i<n;i++)
	if(color[i]==-1)
		dfs(i,0);



// Grid DFS

int rox[]={0,0,1,1,-1,-1,1,-1};
int roy[]={1,-1,1,-1,1,-1,0,0};

void dfs(int x,int y){
	vis[y][x]=VIS;
	for(int i=0;i<8;i++){
		int x_=x+rox[i];
		int y_=y+roy[i];
		if(x_>=0 && y>=0 && x_<N && y_<M && vis[y][x]==UNVIS)
			dfs(x_,y_);
	}
}



// Articulation Points

int hig[1000000],low[1000000],ap[1000000],s_count;

void dfs(int u,int p,int pos){
	hig[u]=low[u]=pos;
	for(int v:g[u]){
		if(v==p) 	continue;
		if(hig[v]==-1){
			if(p==-1)	s_count++;
			dfs(v,u,++pos);
			if(hig[u]<=low[v])	ap[u]=1;	
		}
		low[u]=min(low[u],low[v]);
	}
}

fill(hig,hig+n,-1);
fill(low,low+n,-1);
fill(ap,ap+n,0);
for(int i=0;i<n;i++)
	if(hig[i]==-1){
		s_count=0;	
		dfs(i,-1,0);
		ap[i]=s_count>=2?1:0;
	}


// Articulations Points and Biconnected Components


int hig[1000000],low[1000000],ap[1000000],s_count;
vii wait;
vector< vii > bc;

void dfs(int u,int p,int pos){
	hig[u]=low[u]=pos;
	for(int v:g[u]){
		if(v==p) 	continue;
		if(hig[v]<hig[u])	wait.push_back(ii(u,v));
		if(hig[v]==-1){
			if(p==-1)	s_count++;
			dfs(v,u,++pos);
			if(hig[u]<=low[v]){
				ap[u]=1;
				bc.push_back(vii());
				while(1){
					ii tmp=wait.back();
					wait.pop_back();
					bc.back().push_back(tmp);
					if(tmp.first==u)	break;
				}
			}
		}
		low[u]=min(low[u],low[v]);
	}
}


fill(hig,hig+n,-1);
fill(low,low+n,-1);
fill(ap,ap+n,0);
wait.clear();
bc.clear();
for(int i=0;i<n;i++)
	if(hig[i]==-1){
		s_count=0;	
		dfs(i,-1,0);
		ap[i]=s_count>=2?1:0;
	}
		



// Erathostenes Sieve

vi primes(n,1);
primes[0]=primes[1]=0;
int top=ceil(sqrt(N));
for(int i=2;i<top;i++){
	if(primes[i]==1)
		for(int j=i;i*j<=N;j++)
			primes[i*j]=0;
}

// Greatest Common Divisor

int gcd(int a,int b){return b==0? abs(a): gcd(b,a%b);}

// Extended Euclid Algorithm

ii gcd_ext(int a,int b){
	if(b==0) return a>=0?ii(1,0):ii(-1,0);
	ii res=gcd_ext(b,a%b);
	return ii(res.second,res.first-(a/b)*res.second);
}


// Binary Exponentiation

int bin_exp(int base,int pot){
	int res=1;
	for(;pot>0;pot>>=1){
		if(base&1)
			res=res*base%mod;
		base=base*base%mod;
	}
	return res;
}

// Euler´s Totient Function

int phi(int n){
	if(primes[n]) return n-1;
	int top=(int)ceil(sqrt(n));
	for(int p=2;p<top;p++)
		if(primes[p] && n%p==0){
			n/=p;
			n/=p-1;
		}
}

// Modular Inverse 

int inv = ( gcd_ext(a,mod).first%mod+mod ) % mod;
int inv = bin_exp( a,phi(mod)-1 );

// Modular Binomial Coefficient nCr with mod = prime 

int binomial = fact[n] * bin_exp( fact[r]*fact[n-r]%mod , mod-2 )  %mod;



