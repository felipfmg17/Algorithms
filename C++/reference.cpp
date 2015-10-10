#include <bits/stdc++.h>
#define f(x,n) for(int x=0;x<n;x++)
#define INF 1<<30

using namespace std;

typedef long num;
typedef vector<num> vi;
typedef vector< vi > vvi;
typedef pair<num,num> ii;
typedef vector<ii> vii;
typedef stack<num> si;
typedef queue<num> qi;




/**************** Data Structures *************/

#define lsb(x) x&(-x)

struct Fenwick{
	vi b;
	Fenwick(int n): b(n+1,0) {}

	void update(int i,num v){ 
		for(;i<b.size();i+=lsb(i)) 
			b[i]+=v; 
	}

	num query(int i){ 
		num m=0;  
		for(;i!=0;i-=lsb(i) )
			m+=b[i]; 
		return m;}
};

void r_update(Fenwick b1,Fenwick b2,int i,int j,num v){ 
	b1.update(i,v); 
	b1.update(j+1,-v); 
	b2.update(i,v*(i-1)); 
	b2.update(j+1,-v*j); 
}
num r_query(Fenwick b1,Fenwick b2,int i){ 
	return b1.query(i)*i - b2.query(i); 
}

struct Fenwick2D{
	vvi b;

	Fenwick2D(int l,int h): b(l+1, vi(h+1,0) ) {}

	void update(int x, int y, num v){ 
		for(int i=x;i<b.size();i+=lsb(i)) 
			for(int j=y;j<b[i].size();j+=lsb(j))
				b[i][j]+=v; 
	}

	num query(int x,int y){ 
		num m=0; 
		for(int i=x;i!=0;i-=lsb(i)) 
			for(int j=y;j!=0;j-=lsb(j)) 
				m+=b[i][j]; 
			return m;
	}
	num query(int x1,int y1,int x2,int y2){  
		return query(x2,y2)+query(x1-1,y1-1)-query(x1-1,y2)-query(x2,y1-1); 
	}
};


#define NEUTRO 0

struct SegmentTree{
	num L,R,val,*lazy;
	SegmentTree *left,*right;

	SegmentTree(num  l,num r){	
		L=l; R=r;	
		val=NEUTRO;	
		lazy=NULL; 
		left=right=NULL;
	}

	~SegmentTree(){ 
		if(left) delete left; 
		if(right) delete right; 
	}

	num link(num a,num b){return a+b;}
	num range(num range,num val){ return range*val ;}
	num mix(num a,num b){return a+b;}

	void build(){
		if(left==NULL){	
			left=new SegmentTree( L, (L+R)/2 );	
			right=new SegmentTree( (L+R)/2+1,R);	
		}
		if(lazy!=NULL){
			left->update(L,(L+R)/2,*lazy);	
			right->update((L+R)/2+1,R ,*lazy);
			delete lazy;	
			lazy=NULL;
		}	
	}

	void update(num i,num j,num v){
		if( i>R || j<L ) return;
		if( L>=i && R<=j ){  
			val=mix(val, range(R-L+1,v) ); 
			if(lazy==NULL){
				lazy=new num; 
				*lazy=NEUTRO;} 
				*lazy=mix(*lazy,v); 
				return;
			}  
		build();	
		left->update(i,j,v);	
		right->update(i,j,v);
		val = link( left->val, right->val );	
	}

	num  query(num i,num j){
		if( i>R || j<L ) 
			return NEUTRO;	
		if( L>=i && R<=j ) 
			return val;
		build();	
		return link( left->query(i,j) , right->query(i,j) );	
	}
};


struct UnionFind{
	int sets;	vi p,l;

	UnionFind(int n){ sets=0; f(i,n) make(); }

	void make(){ 
		p.push_back(p.size()); 
		l.push_back(1); 
		sets++; 
	}
	int find(int u){
		if(u!=p[u])
			p[u]=find(p[u]); 
		return p[u];
	}
	void join(int u,int v){	
		u=find(u); v=find(v); 
		if(u!=v){ p[v]=u; l[u]+=l[v]; sets--; } 
	}
};



int find(int u){ return (p[u])==u)? u, (p[u]=find(p[u])); }
void join(int u,int v){ u=find(u);v=find(v); if(u^v) p[u]=v;}

/************ Graph ****************/


#define VIS 1
#define UNVIS -1


typedef int key;

struct Graph{
	int n;
	vvi edges;
	vvi weights;
	vi in_degs;
	vector< set<int> > reps;

	map<key,int> tab;
	vector<key> keys;
	
	Graph(): n(0) {}
	Graph(int nodes): 
		n(nodes), 
		edges(nodes,vi()), 
		weights(nodes,vi()), 
		in_degs(nodes,0), 
		reps(nodes,set<int>()) {}



	void add_node(){
		n++;
		edges.push_back( vi() );
		weights.push_back( vi() ); 
		in_degs.push_back(0); 
		reps.push_back( set<int>() );
	}



	void add_edge(int u,int v,int w){
		if(reps[u].count(v)) 
			return;
		edges[u].push_back(v);
		weights[u].push_back(w);
		in_degs[v]++;
		reps[u].insert(v);	
	}

	int make_vertex(key u){
		if(tab.count(u)==0){
			tab[u]=n;
			keys.push_back(u);
			add_node();
		}
		return tab[u];
	}



	int bfs(int s,vi &res){
		int u=s;
		int nodes=0; 
		qi order;	
		res[u]=0;
		order.push(u);
		while(!order.empty()){
			u=order.front(); 
			order.pop(); 
			nodes++;
			for(int v:edges[u])	
				if(res[v]==UNVIS){
					res[v]=res[u]+1;	
					order.push(v);
				}	
		}	
		return nodes; 
	}


	void dfs(int s,vi &res){
		int u,v;
		vi it(n,0);
		si order;
		u=s;
		res[u]=s;
		order.push(u);
		while(!order.empty()){
			u=order.top();
			if(it[u]<edges[u].size()){
				v=edges[u][it[u]];
				if(res[v]==UNVIS){
					res[v]=s;
					order.push(v);
				}
				it[u]++;
			}
			else
				order.pop();
		}
	}




	bool bipartite(int u,vi &color){
		int v; 
		qi order;
		color[u]=0;	
		order.push(u);
		while(!order.empty()){
			u=order.front(); 
			order.pop();
			for(int v: edges[u]){
				if(color[v]==UNVIS ){
					color[v]=1-color[u];	
					order.push(v);	
				}
				else if(color[v]==color[u]) 
					return false;	
			}	
		} 
		return true; 
	}



	void topo_sort(vi &topo){
		qi order;	int u,v; vi in_degs(this->in_degs);
		f(i,n)	if(!in_degs[i]) order.push(i);
		while(!order.empty()){
			u=order.front(); order.pop();	topo.push_back(u);
			f(i,edges[u].size()){
				v=edges[u][i];	if( !(--in_degs[v]) ) order.push(v);	}
	}	}


	void biconnected(int s,vi &res,vi &artics, vector< vii > &bicon){
		int u,v,p,count=0;
		si order;
		vi it(n,0),hig(n,UNVIS),low(n,UNVIS),parent(n,UNVIS);
		stack< ii > w_edges;
		u=s;
		res[u]=s;
		hig[u]=count;
		low[u]=count++;
		order.push(u);
		while(!order.empty()){
			u=order.top();
			
			if(it[u]<edges[u].size()){
				v=edges[u][it[u]];
				if(res[v]==UNVIS){
					res[v]=VIS;
					hig[v]=count;
					low[v]=count++;
					parent[v]=u;
					order.push(v);
					w_edges.push( ii(u,v) );
					if(u==s)
						artics[s]++;
				}
				else if(v!=parent[u] && hig[u]>hig[v]){
					low[u]=min(low[u],low[v]);					
					w_edges.push( ii(u,v) );
				}
				it[u]++;
			}
			else {
				order.pop();
				if(u==s)
					continue;
				p=parent[u];
				low[p]=min(low[p],low[u]);
				if(low[u]>=hig[p]){
					artics[p]=1;
					bicon.push_back( vii() );
					ii edge;
					while(1){
						edge=w_edges.top();
						w_edges.pop();
						bicon.back().push_back(edge);
						if(edge.first==p)
							break;
					}

				}
				
			}
		}

		artics[s]= artics[s]>=2? 1:0;

	}
	


	void strongly_connected(int s,vi &res,vvi &strongs){
		int u,v,p;
		int count=0;
		vi it(n,0);
		vi hig(n,UNVIS);
		vi low(n,UNVIS);
		si w_vertex;
		si order;
		u=s;
		hig[u]=count;
		low[u]=count++;
		order.push(u);
		w_vertex.push(u);

		while(!order.empty()){
			u=order.top();
			if(it[u]<edges[u].size()){
				v=edges[u][it[u]];
				if(res[v]==UNVIS)
					if(hig[v]==UNVIS){
						hig[v]=count;
						low[v]=count++;
						order.push(v);
						w_vertex.push(v);
					}
					else 
						low[u]=min(low[u],low[v]);
				it[u]++;
			}
			else{
				order.pop();
				res[u]=VIS;

				if(hig[u]==low[u]){
					strongs.push_back(vi());
					while(1){
						int vertex=w_vertex.top();
						w_vertex.pop();
						strongs.back().push_back(vertex);
						if(vertex==u)
							break;
					}
				}
				if(u!=s){
					p=order.top();
					low[p]=min(low[p],low[u]);
				}
			}
		}
		
	}




	
};




int  grid_edge_distance(vvi &grid, vvi &dist, int r,int c){ 
	int dr[]={1,1,0,-1,-1,-1,0,1};	int dc[]={0,1,1,1,0,-1,-1,-1};
	int nodes=0,rr,cc;	queue< ii > order;
	if(grid[r][c]==1){	dist[r][c]=0;	order.push( ii(r,c) );	}
	while(!order.empty()){
		r=order.front().first;	c=order.front().second;	order.pop(); nodes++;
		f(i,8){
			rr=r+dr[i]; 	cc=c+dc[i];
			if(rr>=0 && cc>=0  && grid[rr][cc]==1 && dist[rr][cc]==INF )
				{	dist[rr][cc]=dist[r][c]+1;	order.push( ii(rr,cc) );	}
	}	}	return nodes; }






/************** Mathematics **************/


num mod_pow(num b,num e,num m){
	num mask= 1<<30,res=1;
	for(;mask;mask>>=1){  
		res=(res*res)%m;	
		if( e&mask) res= (res*b)%m;	
	}
	return res;
}

void eratosthenes(num n,vi &numbers){
	numbers.assign(n+1,1);	
	numbers[0]=0; 
	numbers[1]=0; 
	num radix=(num)ceil(sqrt(n));
	for(int i=2;i<=radix+1;i++)	
		if(numbers[i])	
			for(int j=i;j*i<=n;j++)	
				numbers[i*j]=0;
}

void getPrimes(vi &primes, vi &numbers){
	primes.clear();
	f(i,numbers.size())	
		if(numbers[i])	
			primes.push_back(i);
} 

num euler_phi(num n,vi &primes){
	if(binary_search(primes.begin(),primes.end(),n)) 
		return n-1;
	num res=n;	
	num radix=(num)ceil(sqrt(n));
	for(num p: primes)	
		if(p>radix) break;	
		else if( n%p ){ res/=p; res*=p-1;}
	return res;
}

num gcd(num a, num b){
	return (!b? abs(a):gcd(b,a%b));
}

void gcd_extended(num a, num b, num &s, num &t,num &d){
	if(b==0){
		s=a>0?1:-1; 
		t=0; 
		d=abs(a); 
	}else{
		gcd_extended(b,a%b,s,t,d);	
		swap(s,t);  
		t = t-(a/b)*s ;
	}
}

num modInv(num a,num m){ 
	num s,t,d; 
	gcd_extended(a,m,s,t,d); 
	return (s%m+m)%m;
}


void factorization(num n,vi &primes, map<num,num> &fact){
	fact.clear();
	if(binary_search(primes.begin(),primes.end(),n)) fact[n]=1;
	num radix=(num)ceil(sqrt(n));
	for(num p: primes) {
		if(p>radix) break;
		else{	
			num exp=0;
			while(n%p){	exp++; 	n/=p;}  
			if(exp) fact[p]=exp;
		}
	}
}



/************ Geometry  *************/


#define EPS 1e-9

bool equal(double a,double b){return fabs(b-a)<EPS;}

struct Point{
	double x,y;
	Point(double x_,double y_): x(x_), y(y_) {}
	Point operator-(Point p){ return Point(x-p.x,y-p.y); }
	double operator*(Point p){ return x*p.y-y*p.x;}
	double operator~(){ return hypot(x,y);}
	Point operator*(double s){ return Point(s*x,s*y);}
	bool operator==(const Point &p) const { return equal(x,p.x) && equal(y,p.y); }
	bool operator<(const Point &p) const { return   !equal(x,p.x)? x<p.x : equal(y,p.y)? false: y<p.y;}
	Point operator+(Point p){ return Point(x+p.x,y+p.y);}
	double operator%(Point p){return x*p.x+y*p.y;}	
	Point rot(double arc){ return Point(x*cos(arc)-y*sin(arc), x*sin(arc)+y*cos(arc) );}
};


double arc(Point &p,Point &q){ return acos( (p%q)/(~p * ~q) );}

struct Line{
	Point m,d;
	Line(Point &p,Point &q): m(p-q), d(p) {}
	bool operator==(Line &l){ return equal(m*l.m,0) && equal( (d-l.d)*m,0) ;}
	double distance(Point &p){ return fabs( (d-p)*m ) / ~m ;}
	int intersect(Line &l){ return  equal(m*l.m,0) ?  ( equal( (d-l.d)*m, 0) ? INF: 0 )  : 1;  }
	Point intersection(Line &l){return  d - m*(  l.m*(d-l.d)/(l.m*m)  ) ;}
	double distance(Line &l){return equal(m*l.m,0)? distance(l.d): 0 ; }
};




/************ Main **************/


vi visits(50001,UNVIS);
vi dist(500001,UNVIS);
vi position(500001,UNVIS);



ii mdfs(Graph &g,int u,int pos){
	visits[u]=VIS;
	position[u]=pos;
	int v=g.edges[u][0];

	if(dist[v]!=UNVIS){
		dist[u]=dist[v]+1;
		return ii(dis[u]+pos,pos);
	}
	else if(visits[v]==VIS){
		dis[u]=pos-position[v]
	}
}

void problem(){


}




int main()
{
	problem();
	return 0;
}






//  cls && g++ -std=c++11  reference.cpp -o reference && reference