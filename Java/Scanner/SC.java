import java.util.*;
import java.io.*;

class SC{
	int buf_size=100000000;
	byte b[]=new byte[buf_size];
	InputStream in;
	StringTokenizer tk;
	
	SC(InputStream in){
		try{	this.in=in;
		int bytes=in.read(b);
		String st=new String(b,0,bytes);
		tk=new StringTokenizer(st);}
		catch(IOException e){}	}
	
	String next(){	return tk.hasMoreTokens()?tk.nextToken():null;}
	boolean hasNext(){return tk.hasMoreTokens();}
	int nextInt(){return Integer.parseInt(next());}
}