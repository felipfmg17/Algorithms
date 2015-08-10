#include <bits/stdc++.h>
using namespace std;

struct Point{
	double x,y;
	Point(double x_,double y_): x(x_), y(y_) {}
	bool operator==(Point& p){ return x==p.x && y==p.y; }
	bool operator<(Point& p){ return   (x!=p.x)? x<p.x : y<p.y ;}
	Point operator+(Point &p){ return Point(x+p.x,y+p.y);}
	Point operator-(Point &p){ return Point(p.x-x,p.y-y); }
	Point operator(double rad){ return Point(x*cos(rad)-y*sin(rad), x*sin(rad)+y*cos(rad) );}
	Point operator(Point &p){ return Point(x-p.x,y-p.y);}
	double operator*(Point &p){ return x*p.y-y*p.x;}
	double operator%(Point &p){return x*p.x+y*p.y;}
	double operator~{ return hypot(x,y);}
	double arc(){ return atan2(y,x);}
};

double operator^(Point &p,Point &q){ acos( (p%q)/ ~p * ~q );}

struct Line{
	Point m,d;
	Line(Point &u,Point &v): m(u-v), d(u) {}
	bool operator==(Line &l){return (m*l.m)==0 && m*(d - l.d)==0 }
	double dist(Point &p){ return m*(d-p) / ~(d-p) }
	//double dist(Line &l){ }
};



int main(){
	return 0;
}

