import java.util.*;

class SegmentTree{
	int a[];
	int s[];
	
	SegmentTree(int []a){
		this.a=a;
		s=new int[a.length*4];
	}
	
	void build(int p,int L,int R){
		if(L==R)	s[p]=a[L];
		else{
			int half=(L+R)/2;
			build(left(p),L,half);
			build(right(p),half+1,R);
			int pL=s[left(p)];
			int pR=s[right(p)];
			s[p]=value(pL,pR);
		}
	}
	
	int query(int p,int L,int R,int i,int j){
		//System.out.println("p=" + p + " L=" + L + " R=" + R + " i=" + i + " j=" + j);
		if(i<L || j>R || i>R || j<L)	return neutralValue();
		if(i==L && j==R)	return s[p];
		else{
			int half=(L+R)/2;
			int pL=query(left(p),L,half,i,Math.min(j,half));
			int pR=query(right(p),half+1,R,Math.max(half+1,i),j);
			return value(pL,pR);
		}
	}
	
	void update(int p,int L,int R,int i,int j){
		//System.out.println("p=" + p + " L=" + L + " R=" + R + " i=" + i + " j=" + j);
		if(i<L || j>R || i>R || j<L)	return;
		
		if(L==i && R==j)	build(p,L,R);
		else{
			int half=(L+R)/2;
			update(left(p),L,half,i,Math.min(j,half));
			update(right(p),half+1,R,Math.max(half+1,i),j);
			int pL=s[left(p)];
			int pR=s[right(p)];
			s[p]=value(pL,pR);
		}
	}
	
	int left(int p){return p*2+1;}
	
	int right(int p){return p*2+2;}
	
	int neutralValue(){ return 0;}
	
	int value(int pL,int pR){return pL+pR;}
}