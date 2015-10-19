///////// NEW REFERENCE ///////

#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int ,int> ii;
typedef vector< ii > vii;
typedef long long lld;

// Fenwick Tree

#define lsb(x) x&(-x)

int ft[1000000];
void u(int i,int v){for(;i<n;i+=lsb(i))ft[i]+=v;}
int q(int i){int m=0; for(;i!=0;i-=lsb(i))m+=ft[i];}

// Union Find

vi uf;
void make(){uf.push_back(uf.size());}
int find(int u){if(u!=uf[u]) return uf[u]=find(uf[u]);}
void join(int u,int v){u=find(u);v=find(v); if(u!=v) uf[u]=v;}

// Union Find: set count and set size

vi uf,uf_s;
int uf_n;

void make(){
	uf.push_back(uf.size());
	uf_s.push_back(1);
	uf_n++;
}

int find(int u){
	if(u!=uf[u]) 
		return uf[u]=find(uf[u]);
}

void join(int u,int v){
	u=find(u);v=find(v);
	if(u!=v) {
		uf[u]=v;
		uf_s[v]+=uf_s[u];
	}
}

uf.clear();
uf_s.clear();
uf_n=0;

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



// Articulation Points and Bridges

int hig[1000000],low[1000000],ap[1000000],sc;
vii bri;

void dfs(int u,int p,int pos){
	hig[u]=low[u]=pos;
	for(int v:g[u]){
		if(v==p) 	continue;
		if(hig[v]==-1){
			if(p==-1)	sc++;
			dfs(v,u,pos+1);
			if(hig[u]<=low[v])	ap[u]=1;
			if(hig[u]<low[v])	bri.push_back(ii(u,v));	
		}
		low[u]=min(low[u],low[v]);
	}
}

fill(hig,hig+n,-1);
fill(low,low+n,-1);
fill(ap,ap+n,0);
bri.clear();
for(int i=0;i<n;i++)
	if(hig[i]==-1){
		sc=0;	
		dfs(i,-1,0);
		ap[i]=(sc>=2)?1:0;
	}


// Articulations Points and Biconnected Components

int hig[1000000],low[1000000],ap[1000000],sc;
vii wait;
vector< vii > bc;

void dfs(int u,int p,int pos){
	hig[u]=low[u]=pos;
	for(int v:g[u]){
		if(v==p) 	continue;
		if(hig[v]<hig[u])	wait.push_back(ii(u,v));
		if(hig[v]==-1){
			if(p==-1)	sc++;
			dfs(v,u,pos+1);
			if(hig[u]<=low[v]){
				ap[u]=1;
				bc.push_back(vii());
				while(1){
					ii tmp=wait.back();	wait.pop_back();
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
		sc=0;	
		dfs(i,-1,0);
		ap[i]=sc>=2?1:0;
	}

// Strongly Connected Components

int hig[1000000],low[1000000],vis[1000000];
int scc[1000000],scc_n;
vi wait;

void dfs(int u,int pos){
	hig[u]=low[u]=pos; vis[u]=1;
	wait.push_back(u);
	for(int v:g[u]){
		if(hig[v]==-1)dfs(v,pos+1);
		if(vis[v]==1)low[u]=min(low[u],low[v]);
	}
	if(hig[u]==low[u]){
		while(1){
			int v=wait.back(); wait.pop_back();
			vis[v]=0;
			scc[v]=scc_n;
			if(u==v) break;
		}
		scc_n++;
	}
}

fill(hig,hig+n,-1);
fill(low,low+n,-1);
fill(vis,vis+n,0);
fill(scc,scc+n,-1);
wait.clear();
scc_n=0;
for(int i=0;i<n;i++)
	if(hig[i]==-1)
		dfs(i,0);


// SSC to DAG

vi dag[1000000];
set<int> reps[1000000];

fill(dag,dag+scc_n,vi());
fill(reps,reps+scc_n,set<int>());
for(int i=0;i<n;i++)
	for(int v:g[i]){
		a=scc[i];	b=scc[v];
		if(a!=b)
			if(reps[a].count(b)==0){
				dag[a].push_back(b);
				reps[a].insert(b);
			}	
	}

// Erathostenes Sieve

int primes[1000000];

fill(primes,primes+k,1)
primes[0]=primes[1]=0;
int top=ceil(sqrt(N));
for(int i=2;i<top;i++){
	if(primes[i]==1)
		for(int j=i;i*j<=N;j++)
			primes[i*j]=0;
}

// Primes to list;

vi prims;

prims.clear();
for(int i=0;i<k;i++)
	if(primes[i]==1)
		prims.push_back(i);


// Greatest Common Divisor

int gcd(int a,int b){return b==0? abs(a): gcd(b,a%b);}

// Extended Euclid Algorithm

ii gcd_ext(int a,int b){
	if(b==0) return a>=0?ii(1,0):ii(-1,0);
	ii res=gcd_ext(b,a%b);
	return ii(res.second,res.first-(a/b)*res.second);
}


// Binary Exponentiation

int bin_exp(int b,int e){
	int res=1;
	for(;e>0;e>>=1){
		if(b&1)	res=res*b%mod;
		b=b*b%mod;
	}
	return res;
}

// Euler's Totient Function

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

int bin=fact[r]*fact[n-r] % mod;
bin=fact[n]*bin_exp(bin,mod-2)%mod;     









// Fenwick Tree Range Updates

void update(int i,int j,int v){ 
	u1(i,v); 
	u1(j+1,-v); 
	u2(i,v*(i-1)); 
	u2(j+1,-v*j); 
}

int query(int i){ 
	return q1(i)*i - q2(i); 
}


// Fenwick Tree 2D

int b[m][n];

void update(int x, int y,int v){ 
	for(int i=x;i<m;i+=lsb(i)) 
		for(int j=y;j<n;j+=lsb(j))
			b[i][j]+=v; 
}

int query(int x,int y){ 
	int m=0; 
	for(int i=x;i!=0;i-=lsb(i)) 
		for(int j=y;j!=0;j-=lsb(j)) 
			m+=b[i][j]; 
		return m;
}

int query(int x1,int y1,int x2,int y2){  
	return query(x2,y2)+query(x1-1,y1-1)-query(x1-1,y2)-query(x2,y1-1); 
}




