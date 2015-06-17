import java.io.*;
import java.util.*;

class InputReader {
    BufferedReader reader;
    StringTokenizer tokenizer=null;

    InputReader(InputStream stream){
        reader=new BufferedReader(new InputStreamReader(stream),1000000);}

    String next(){
        while(tokenizer==null || !tokenizer.hasMoreTokens()){
            try{tokenizer=new StringTokenizer(reader.readLine());}
			catch(IOException e){throw new RuntimeException(e);}
        }
        return tokenizer.nextToken();
    }
	
	boolean hasNext(){
		return tokenizer.hasMoreTokens();
	}
	
	String nextLine(){
		try{return reader.readLine();}
		catch(IOException e){throw new RuntimeException(e);}
	}
	
    int nextInt(){return Integer.parseInt(next());}
	double nextDouble(){return Double.parseDouble(next());}
	long nextLong(){return Long.parseLong(next());}
	byte nextByte(){return Byte.parseByte(next());}
}