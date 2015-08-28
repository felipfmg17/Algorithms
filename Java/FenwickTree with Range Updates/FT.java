class FT{
	int b1[],b2[];
	FT(int n){	b1=new int[n+1]; b2=new int[n+1]; Arrays.fill(b1,0); Arrays.fill(b2,0);}
	int lsb(int i){	return i&(-i);}
	
	void u(int i,int j,int v){	u(b1,i,v);	u(b1,j+1,-v);	u(b2,i,v*(i-1));	u(b2,j+1,-v*j);}
	
	int q(int i){ return q(b1,i)*i-q(b2,i);}
	
	int q(int i,int j){	return q(j)-(i==1?0:q(i-1));}




	void u(int[] b,int i,int v){for(;i<b.length;i+=lsb(i))	b[i]+=v;}

	int q(int[] b,int i){	int m=0;	for(;i!=0;i-=lsb(i))	m+=b[i];	return m;}	
}