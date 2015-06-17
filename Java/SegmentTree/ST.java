import java.util.*;

class ST<E>{
	E a[];	Q s[];
	int l,r,p;
	
	ST(E[] aa){
		a=aa;
		s=new Q[a.length*4];
		l=0; r=a.length-1; p=0;
		build(p,l,r);}
	
	void build(int p,int L,int R){
		if(L==R){	s[p]=Q.<E>E2Q(a[L]); return; }
		int h=(L+R)/2;
		build(left(p),L,h);
		build(right(p),h+1,R);
		s[p]=s[left(p)].merge(s[right(p)]);}
	
	Q q(int p,int L,int R,int i,int j){
		if(i<L || j>R || i>R || j<L)	return Q.n();
		if(i==L && j==R)	return s[p];
		int h=(L+R)/2;
		Q pL=q(left(p),L,h,i,Math.min(j,h));
		Q pR=q(right(p),h+1,R,Math.max(h+1,i),j);
		return pL.merge(pR);}
	
	void u(int p,int L,int R,int i,int j){
		if(i<L || j>R || i>R || j<L)	return;		
		if(L==i && R==j){build(p,L,R); return;}
		int h=(L+R)/2;
		u(left(p),L,h,i,Math.min(j,h));
		u(right(p),h+1,R,Math.max(h+1,i),j);
		s[p]=s[left(p)].merge(s[right(p)]);}
	
	Q q(int i,int j){return q(p,l,r,i,j);}
	
	void u(int i,int j){u(p,l,r,i,j);}
	
	int left(int p){return p*2+1;}
	
	int right(int p){return p*2+2;}
}


class Q{		
	/*values*/
	
	Q(/*values*/){
		/*fill values*/
	}
	
	Q merge(Q q){			
		return new Q(/*values*/);
	}
	
	static Q n(){
		return new Q();
	}
	
	static <E> Q E2Q(E e){
		return new Q();
	}
}

