class ST{
	int a,b,h;	ST L,R; 	V v,l;
	ST(int aa,int bb,V vv){
		v=vv; a=aa; b=bb;	h=(a+b)/2;  if(a==b) return;
		L=new ST(a,h,v);	R=new ST(h+1,b,v);	}
	V q(int i,int j){
		if(i<a || i>b || j>b || j<a) return V.n();
		if(i==a && j==b) return v;
		if(l!=null){	L.u(a,h,l);	R.u(h+1,b,l);	l=null;	}
		return V.f( L.q(i,Math.min(h,j)) , R.q(Math.max(h+1,i),j) );	}	
	void u(int i,int j,V u){
		if(i<a || i>b || j>b || j<a) return;		
		if(i==a && j==b){	v= V.f( V.u(i,j,u) , v);	if(a!=b) l=V.f(u,l);	}
		else{	if(l!=null){	L.u(a,h,l);	R.u(h+1,b,l);	l=null;	}
		L.u(i,Math.min(h,j),u);		R.u(Math.max(h+1,i),j,u);
		v=V.f(L.v,R.v);	}	}
}

class V{
	V(){}
	static V f(V a,V b){ return new null;}
	static V n(){return null;}
	static V u(int a,int b,V v){return null;}
}




/*
	Class ST: SegmentTree node representing the range [a,b]
		
		Attributes
			a,b,h: int 		--- Range of this node,h is the half of the range
			L,R : ST		--- left and rigth child
			v,l : V			--- values of this node, lazy values 
		
		Methods
			q(int a,int b):V			--- r = root where start to find, a-b range of the query
			u(int a,int b,V v):void		--- r = root where start to find, a-b range of the update
			


		Complementary Info
		
			String toString(String s){
				String l,r;
				if(L!=null)
				l=L.toString(s+"   ");
				else l="\n";
				if(R!=null)
				r=R.toString(s+"   ");
				else r="\n";
				return s+s+"--("+a+","+b+")="+v.sum+"\n"+l+r;
			}
			
	Class V: Represents the values of a ST node
	
		Attributes
		
		Methods
		
			f(V a,V b):V			---	combine values a and b
			n(): V					--- neutral value
			u(int a,int b,V v):	V	---set de value of a range

*/