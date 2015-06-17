import java.util.*;

class UF{
	int size=0,sets=0;
	List<Integer> p,r,l;

	UF(int n){
		p=new ArrayList<Integer>(n);
		r=new ArrayList<Integer>(n);
		l=new ArrayList<Integer>(n);	
		for(int i=0;i<n;i++)	makeSet();
	}
	
	void makeSet(){
		p.add(size);	r.add(0);	l.add(1);
		size++;	sets++;
	}
	
	int findSet(int a){
		if(p.get(a)==a)	return p.get(a);
		p.set(a,findSet(p.get(a)));
		return p.get(a);
	}
	
	boolean isSameSet(int a,int b){	return findSet(a)==findSet(b);	}
	
	void joinSets(int a,int b){
		if(!isSameSet(a,b)){
			int x=findSet(a);	int y=findSet(b);
			if(r.get(x)>r.get(y))
			{	p.set(y,x);	l.set(x,l.get(x)+l.get(y));	}
			else{
				p.set(x,y);
				l.set(y,l.get(x)+l.get(y));
				if(r.get(x)==r.get(y))	r.set(y,r.get(y)+1);
			}
			sets--;
		}
	}
	
	int length(int a){	return l.get(findSet(a));	}
}