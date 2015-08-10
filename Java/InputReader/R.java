
class B{
	BufferedReader buf;
	B(InputStream in){buf=new BufferedReader(new InputStreamReader(in), 256*1024);}
	String nextLine(){	try{return buf.readLine();}catch(IOException e){} return null;}
}

class S{
	StringTokenizer tok;
	S(String line){tok=new StringTokenizer(line);}
	String next(){return tok.nextToken();}
	boolean hasNext(){return tok.hasMoreTokens();}
	int nextInt(){return Integer.parseInt(next());}
}
