

class UnionFind{
	private: vector<int> p,rank;
	
	public:
	UnionFind(int n){
		rank.assign( n,0);
		p.assign(n,0); for( inti i=0;i<n;i++) p[i]=i;
	}
	
	int findSet(int i){
		return (p[i]==i)?i:(p[i]=findSet(p[i]));
	}
	
	bool isSameSet(int i;int j){
		if(!isSameSet(i,j)){
			int x=findSet(i),y=findSet(j);
			if(rank[x] >rank[y])
				p[y]=x;
			else{
				p[x]=y;
				if(rank[x]==rank[y])
					rank[y]++;
			}	
		}
	}
}