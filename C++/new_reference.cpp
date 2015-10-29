///////// NEW REFERENCE ///////

#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int ,int> ii;
typedef vector< ii > vii;
typedef long long lld;


// Compilation

cls && g++ -std=c++11 main.cpp -o main


// Fast I/0

cin.sync_with_stdio(false);
cin.tie(NULL);

// Fenwick Tree

struct FenwickTree{
	int n; vi ft;
	FenwickTree(int n_){n=n_+1; ft.assign(n,0);}
	int lsb(x){return x&(-x);}
	void update(int i,int v){for(;i<n;i+=lsb(i))ft[i]+=v;}
	int query(int i){int m=0; for(;i!=0;i-=lsb(i))m+=ft[i]; return m;}
	int query(int i,int j){return query(j)-query(i-1);}
};

"No index 0, increment n+1"
"index from 1 to n"


// Fenwick Tree Range Updates

struct FenwickTreeRange{
	FenwickTree ft1,ft2;

	FenwickTreeRange(int n): ft1(n),ft2(n) {}

	void update(int i,int j,int v){ 
		ft1.update(i,v); ft1.update(j+1,-v); 
		ft2.update(i,v*(i-1)); ft2.update(j+1,-v*j); 
	}

	int query(int i){ return ft1.query(i)*i - ft2.query(i); }

	int query(int i,int j){ return query(j)-query(i-1);}
};


// Union Find

struct UnionFind{
	vi uf;
	void make(){uf.push_back(uf.size());}
	int find(int u){if(u!=uf[u]) return uf[u]=find(uf[u]);}
	void join(int u,int v){u=find(u);v=find(v); if(u!=v) uf[u]=v;}
};

// Union Find: set count and set size

struct UnionFind{
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
};

"set uf_n to zero after object creation"
"uf_n: number of disjoin sets"
"uf_s[i]: size of disjoin set i"
"uf: parents, root of each disjoin set"


// Segment Tree

struct node{
	int x;
	node(){	x=0; }
	node(int x_){	x=x_;	}
};

node join(node n1,node n2){
	return node(n1.x+n2.x);
}


struct SegmentTree{
	vector<node> st;

	SegmentTree(int n) :
		st(n*4,node()) {}

	int lefts(int x){return x<<1;}
	int rights(int x){ return (x<<1)+1;}

	void build(int p,int L,int R,vi &ar){
		if(L==R) st[p]=node(ar[L]);
		else{
			int h=(L+R)>>1;
			build(lefts(p),L,h,ar);
			build(rights(p),h+1,R,ar);
			st[p]=join(st[lefts(p)],st[rights(p)]);
		}
	}

	node query(int p,int L,int R,int i,int j){
		if(i>R  || j<L) return node();
		if(L>=i && R<=j) return st[p];
		int h=(L+R)>>1;
		node n1=query(lefts(p),L,h,i,j);
		node n2=query(rights(p),h+1,R,i,j);
		return join(n1,n2);
	}

	void update(int p,int L,int R,int i,int v){
		if(i>R  || i<L) return;
		if(R==L){
			st[p]=node(v);
			return;
		} 
		int h=(L+R)>>1;
		update(lefts(p),L,h,i,v);
		update(rights(p),h+1,R,i,v);
		st[p]=join(st[lefts(p)],st[rights(p)]);
	}
};

"implement node(),joind() "
"Default constructor must provide a neutral value"
"join(): handle how two segments are joined "


//Segment Tree Lazy Propagation

struct node{
	int x;
	node(){x=9999999;}
	node(int x_) { x=x_; }
	void replace(int v,int L,int R){ x=v; }
};

node join(node n1,node n2){
	return node(min(n1.x,n2.x));
}

int combine(int lazy,int v){
	return v;
}

struct SegmentTree{
	vector<node> st;
	vector< int* > lazy;

	SegmentTree(int n) : 
		st(n*4,node()), 
		lazy(n*4,(int*)NULL) {}

	int lefts(int x){return x<<1;}
	int rights(int x){ return (x<<1)+1;}

	void build(int p,int L,int R,vi &ar){
		if(L==R) st[p]=node(ar[L]);
		else{
			int h=(L+R)>>1;
			build(lefts(p),L,h,ar);
			build(rights(p),h+1,R,ar);
			st[p]=join(st[lefts(p)],st[rights(p)]);
		}
	}

	void propagate(int p,int L,int R){
		if( lazy[p]!= NULL){
			int h=(L+R)>>1;
			update(lefts(p),L,h,L,h, *lazy[p] );
			update(rights(p),h+1,R,h+1,R, *lazy[p] );
			delete lazy[p];
			lazy[p]=NULL;
		}
	}

	node query(int p,int L,int R,int i,int j){
		if(i>R  || j<L) return node();
		if(L>=i && R<=j) return st[p];
		propagate(p,L,R);
		int h=(L+R)>>1;
		node n1=query(lefts(p),L,h,i,j);
		node n2=query(rights(p),h+1,R,i,j);
		return join(n1,n2);
	}

	void update(int p,int L,int R,int i,int j,int v){
		if(i>R  || j<L) return;
		if(L>=i && R<=j){
			st[p].replace(v,L,R);
			if(lazy[p]==NULL) lazy[p]=new int(v);
			else *lazy[p]=combine(*lazy[p],v);
			return;
		} 
		propagate(p,L,R);
		int h=(L+R)>>1;
		update(lefts(p),L,h,i,j,v);
		update(rights(p),h+1,R,i,j,v);
		st[p]=join(st[lefts(p)],st[rights(p)]);			
	}
};

"implement node(),combine(),join(),replace()"


// Dynamic Segment Tree 

struct node{
	lld x;
	node(){	x=-99999999; }
	node(lld x_) { x=x_;}
	void replace(lld v,lld L,lld R){ x=v;}
};

node join(node n1,node n2){
	return node(max(n1.x,n2.x));
}

lld combine(lld lazy,lld v){
	return v;
}


struct SegmentTree{
	SegmentTree *left,*right;
	lld L,R,*lazy;
	node val;

	SegmentTree(lld L_, lld R_): val() {
		L=L_; R=R_;
		left=right=NULL;
		lazy=NULL;
	}

	~SegmentTree(){
		if(lazy!=NULL) delete lazy;
		if(left!=NULL) delete left;
		if(right!=NULL) delete right;
	}

	void build(vector<lld > &ar){
		if(L==R) val=node(ar[L]);
		else{
			propagate();
			left->build(ar);
			right->build(ar);
			val=join(left->val,right->val);
		}
	}

	void propagate(){
		if(left==NULL){
			left=new SegmentTree(L,(L+R)/2);
			right=new SegmentTree((L+R)/2+1,R);
		}
		if(lazy!=NULL){
			left->update(left->L,left->R,*lazy);	
			right->update(right->L,right->R ,*lazy);
			delete lazy;	
			lazy=NULL;
		}
	}

	node query(lld  i,lld j){
		if(i>R || j<L) return node();	
		if(L>=i && R<=j) return val;
		propagate();	
		return join(left->query(i,j),right->query(i,j));	
	}

	void update(lld i,lld  j,lld v){
		if( i>R || j<L ) return;
		if( L>=i && R<=j ){  
			val.replace(v,L,R);
			if(lazy==NULL) lazy=new lld(v);
			else *lazy=combine(*lazy,v);
			return;
		}  
		propagate();	
		left->update(i,j,v);	
		right->update(i,j,v);
		val=join(left->val,right->val);	
	}	
};



// Count Connected Components

int cc;
vector< vi > vis;

void dfs(int u){
	vis[u]=1;
	for(int v:g[u])
		if(vis[v]==0)
			dfs(v);
}

cc=0;
vis.assign(n,0);
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


"GRAY TO GRAY: CYCLE EDGE"
"GRAY TO WHITE: NEW NODE EDGE"
"GRAY TO BALCK: FORWARD EDGE"



// Bipartite Check (Bicoloring)

vi color;

bool dfs(int u,int c){
	color[u]=c;
	for(int v:g[u])
		if(color[v]==-1)
			if(!dfs(v,c^1))	return false;
		else if(color[v]==color[u])	return false;	
	return true;
}

color.assign(n,-1);
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
		if(x_>=0 && y>=0 && x_<n && y_<m && vis[y][x]==UNVIS)
			dfs(x_,y_);
	}
}



// Articulation Points and Bridges

vi hig,low,ap;
int sc;
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

hig.assign(n,-1);
low.assign(n,-1);
ap.assign(n,0);
bri.clear();
for(int i=0;i<n;i++)
	if(hig[i]==-1){
		sc=0;	
		dfs(i,-1,0);
		ap[i]=(sc>=2)?1:0;
	}

"ap: articulation points"
"sc: source count, determines whether the root is ap"


// Articulations Points and Biconnected Components

int sc;
vi hig,low,ap;
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


hig.assign(n,-1);
low.assign(n,-1);
ap.assign(n,0);
wait.clear();
bc.clear();
for(int i=0;i<n;i++)
	if(hig[i]==-1){
		sc=0;	
		dfs(i,-1,0);
		ap[i]=sc>=2?1:0;
	}

"bc : biconnected components"

// Strongly Connected Components

int scc_n;
vi hig,low,vis,scc,wait;

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

hig.assin(n,-1);
low.assign(n,-1);
vis.assign(n,0);
scc.assign(n,-1);
wait.clear();
scc_n=0;
for(int i=0;i<n;i++)
	if(hig[i]==-1)
		dfs(i,0);


" ssc[i] : tells which scc node i belongs to"
" scc_n : counts the number of ssc "

// SSC to DAG

vector< vi > dag;
vector< set<int> > reps;

void dag(){
	dag.assign(scc_n,vi());
	reps.assign(scc_n,set<int>());
	for(int i=0;i<n;i++)
	for(int v:g[i]){
		a=scc[i];	b=scc[v];
		if(a!=b)
			if(reps[a].count(b)==0){
				dag[a].push_back(b);
				reps[a].insert(b);
			}	
	}
}

"n: nodes in orignal graph"
"scc_n : nodes in the dag"

// Erathostenes Sieve

int primes[1000000];

fill(primes,primes+k,1);
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
		if(e&1)	res=res*b%mod;
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

