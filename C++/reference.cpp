#include <bits/stdc++.h>
#define f(x,n) for(int x=0;x<n;x++)
#define INF 1<<30

using namespace std;

typedef vector<int> vi;
typedef stack<int> si;
typedef queue<int> qi;
typedef pair<int,int> ii;
typedef vector<ii> vii;


/************************************************************************** Data Structures ************************************************************/





/************************************************************************** Geometry 2D ****************************************************************/

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

struct Segment{
	Point a,b,m;
	Segment(Point &p,Point &q): m(p-q), a(p), b(q) {}
};







/******************************************************************* Graph *******************************************************************************/

struct Graph{
	int n;
	map<int,int> t1;
	vi t2;

	vector< vi > cons;
	vector< vi > wei;
	vi in_degs;
	vector< set<int> > reps;
	
	Graph(): n(0) {}
	Graph(int nodes) : n(nodes), cons( nodes,vi() ), wei( nodes,vi() ), in_degs(nodes,0), reps(nodes, set<int>() ) {}


	void add_node(int u){
		if(t1.count(u)==0){ 
			t1[u]=n++;	t2.push_back(u);
			cons.push_back( vi() );
			wei.push_back( vi() ); 
			in_degs.push_back(0); 
			reps.push_back( set<int>() );
	}	}


	void add_edge(int u,int v,int w){
		add_node(u); add_node(v);
		int a=t1[u],b=t1[v];
		if(reps[a].count(b)) return;
		cons[a].push_back(b);
		wei[a].push_back(w);
		in_degs[b]++;
		reps[a].insert(b);	}


	int edge_distance(int u,vi &dist){
		int v,nodes=0;	qi order;	dist[u]=0;	order.push(u);
		while(!order.empty()){
			u=order.front();	order.pop();	nodes++;
			f(i,cons[u].size()){
				v=cons[u][i];	if(dist[v]==INF){ order.push(v);	dist[v]=dist[u]+1; }
	}	}return nodes; }


	void topo_sort(vi &topo){
		qi order;	int u,v; vi in_degs(this->in_degs);
		f(i,n)	if(!in_degs[i]) order.push(i);
		while(!order.empty()){
			u=order.front(); order.pop();	topo.push_back(u);
			f(i,cons[u].size()){
				v=cons[u][i];	if( !(--in_degs[v]) ) order.push(v);	}
	}	}

	bool bicolor(int u,vi &color){
		int v; 	qi order;	color[u]=0;	order.push(u);
		while(!order.empty()){
			u=order.front(); order.pop();
			f(i,cons[u].size()){
				v=cons[u][i];
				if(color[v]==INF){	color[v]=1-color[u];	order.push(v);	}
				else if(color[v]==color[u]) return false;	
	}	} return true; }


};




int  grid_edge_distance(vector< vi > &grid, vector< vi > &dist,int r,int c){
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








int main(){

	return 0;
}



//  cls && g++ reference.cpp -o reference