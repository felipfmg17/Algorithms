class FT{
	int t[][];
	FT(int x,int y){	t=new int[x+1][y+1];	for(int i=0;i<t.length;i++) Arrays.fill(t[i],0);}
	int lsb(int i){	return i&(-i);}
	void u(int x,int y,int v){for(;x<t.length;x+=lsb(x)) 	 for(int j=y;j<t[x].length;j+=lsb(j))  t[x][j]+=v;}
	int q(int x1,int y1,int x2,int y2){	return q(x2,y2)+q(x1-1,y1-1)-q(x2,y1-1)-q(x1-1,y2);}
	int q(int x,int y){	int m=0; for(;x!=0;x-=lsb(x)) for(int j=y;j!=0;j-=lsb(j))	m+=t[x][j]; return m;}
}

/*

public String toString(){
	StringBuilder sb=new StringBuilder();
	sb.append("\nMatrix\n");
	for(int i=1;i<t.length;i++){
		sb.append("pos "+i+": ");
		for(int j=1;j<t[i].length;j++)	sb.append(t[i][j]+" ");	}			
		sb.append("\n");
	}	
	return sb.toString();
}

*/