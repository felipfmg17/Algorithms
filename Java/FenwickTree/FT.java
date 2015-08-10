class FT{
	int t[];
	FT(int n){	t=new int[n+1];	Arrays.fill(t,0);}
	int lsb(int i){	return i&(-i);}
	void u(int i,int v){for(;i<t.length;i+=lsb(i))	t[i]+=v;}
	int q(int i,int j){	return q(j)-(i==1?0:q(i-1));}
	int q(int i){	int m=0; for(;i!=0;i-=lsb(i))	m+=t[i]; return m;}
}