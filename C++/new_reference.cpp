///////// NEW REFERENCE ///////


// DFS


void dfs(int u){
	vis[u]=VIS;
	for(int v:g[u])
		if(vis[v]==UNVIS)
			dfs(v);
}


// Single Source Shortest Path Unweighted Graph


vi dist(n,INF);
for(int i;i<n;i++){
	if(dist[i]==INF){
		deque<int> order();
		order.push_back(i);
		dist[i]=0;
		while(!order.empty()){
			int u=order.front();
			order.pop_front();
			for(int v:g[u])
				if(dist[v]!=INF){
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

vi color;

bool dfs(int u,int c){
	color[u]=c;
	for(int v:g[u]){
		if(color[v]==-1)
			if(!dfs(v,c^1))
				return false;
		else if(color[v]==color[u])
			return false;
	}
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
		if(x_>=0 && y>=0 && x_<N && y_<M && vis[y][x]==UNVIS)
			dfs(x_,y_);
	}
}


// Articulations Points and Biconnected Components
// Tarjan Algorithm

vi hig,low,ap;
vii wait;
vector< vii > bc;
int s_count;

dfs(int u,int p,int pos){
	hig[u]=low[u]=pos;
	for(int v:g[u]){
		if(v==p) continue;
		if(p==-1)
			s_count++;
		if(hig[v]<hig[u])
			wait.push_back(ii(u,v));
		if(hig[v]==-1){
			dfs(v,u,pos+1);
			if(hig[u]<=low[v]){
				ap[u]=1;
				bc.push_back(vii());
				while(1){
					ii tmp=wait.top();
					wait.pop_back;
					bc.back().push_back(tmp);
					if(tmp.first==u)
						break;
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
		s_count=0;	
		dfs(i,-1,0);
		ap[i]=s_count>=2?1,0;
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

inv=(gcd_ext(a,mod).first%mod+mod)%mod;
inv=bin_exp(a,phi(mod)-1);

// Modular Binomial Coefficient nCr with mod = prime 

fact[n] * bin_exp( fact[r]*fact[n-r]%mod , mod-2 )  %mod;



