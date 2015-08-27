#include <bits/stdc++.h>
#define f(x,n) for(int x=0;x<n;x++)
#define ri(x) scanf("%d",&x)
#define rd(x) scanf("%lf",&x);
#define INF 1<<30

using namespace std;

typedef vector<int> vi;
typedef stack<int> si;
typedef queue<int> qi;
typedef pair<int,int> ii;
typedef vector<ii> vii;


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

#define G_SIZE 1000000


struct Graph{
	int n;
	set<int> nodes;
	vector< vi > cons;
	vector< vi > weights;
	vector< set<int> > reps;
	vi in_degrees;

	Graph() : cons(G_SIZE,vi ()), weights(G_SIZE, vi () )  {}


	void edge_distance(int u,vi &dist){
		dist.assign(n,INF);	dist[u]=0;
		qi order;	order.push(u);
		while(!order.empty()){
			u=order.front();	order.pop();
			f(i,cons[u].size()){
				int v=cons[u][i];
				if(dist[v]+1<INF){ order.push(v);	dist[v]=dist[u]+1; }
		}	}	}

/*
	bool cicle(int u){
		vi vis(n,-1); vis[u]=0;
		qi order; order.push_back(u);
		while(!order.size()){
			u=order.back(); 	order.pop_back();
			vis[u]=1;
			f(i,cons[u].size()){

			}
		}
	}



	*/
};





int main(){

	double x,y;
	vector< Point > points;

	f(i,5){
		rd(x); rd(y);
		points.push_back(Point(x,y));
	}
	

	printf("\n modulo %.2lf ",~(points[0]*10));
	Point sum=points[1]+points[2];
	printf("\n suma = %.2lf,%.2lf ",sum.x,sum.y);
	Point dif=points[0]-sum ;
	printf("\n diferencia  %lf %lf\n",dif.x,dif.y);
	printf("\n cruz %lf \n",points[1]*points[2]);

	printf("iguales: %s \n",points[0]==points[1]?"verdadero":"falso");
	printf("menor: %s ",points[0]<points[2]?"verdadero":"falso");
	
/*
	sort(points.begin(),points.begin()+5);
	printf("\n\n");
	f(i,5){
		printf("%.2lf,%.2lf\n",points[i].x,points[i].y);
	}
*/

	Line l1(points[0],points[1]);
	Line l2(points[2],points[3]);

	printf("\nLineas iguales : %s",l1==l2?"verdadero":"falso");
	printf("\nPuntos de interseccion %d",l1.intersect(l2));
	Point inter=l1.intersection(l2);
	printf("\nPunto de interseccion %lf,%lf",inter.x,inter.y);
	printf("\nDistancia punto recta %lf",l1.distance(points[4]));

	return 0;
}

