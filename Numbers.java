import java.util.*;

class Numbers
{
	public static long mod(long a,long m)
	{	a%=m;	return a>=0?a:a+m;	}
	
	public static long gcd(long a,long b){
		for(long t;b!=0;)
		{t=b;	b=a%b;	a=t;}
		return Math.abs(a);
	}
	
	public static long lcm(long a,long b)
	{	return (a*b)/gcd(a,b);	}
	
	public static long modPow(long base,long exp,long m){
		long mask=1<<62,res=1;
		for(;mask!=0;mask>>>=1){
			res=(res*res)%m;
			if((exp&mask)!=0)
				res=(res*base)%m;
		}	return res;
	}
	
	public static boolean[] sieve(int n){
		boolean s[]=new boolean[n+1];
		Arrays.fill(s,true);
		s[0]=false; s[1]=false;
		for(int i=2;i*i<n;i++)
			if(s[i]==true)
				for(int j=i;j*i<=n;j++)
					s[i*j]=false;			
		return s;
	}
	
	public static SortedSet<Long> primes(boolean[] sieve){
		SortedSet<Long> s=new TreeSet<Long>();
		for(int i=0;i<sieve.length;i++)
			if(sieve[i]==true) s.add((long)i);
		return s;
	}
		
	public static SortedMap<Integer,Integer> factorize(int n,SortedSet<Long> primes){
		SortedMap<Integer,Integer> f=new TreeMap<Integer,Integer>();
		for(long p : primes)
			if(primes.contains((long)n))
			{f.put((int)n,1);	break;}
			else if(p<n){
				int k=0;
				while(n%p==0)
				{n/=p;	k++;}
				f.put((int)p,k);
			}
		return f;
	}
	
	public static long phi(long n,SortedSet<Long> primes){
		long res=n;
		for(long p : primes)
			if(p>n)	break;
			else if(n%p==0)
			{res/=p;	res*=p-1;}
		return res;
	}
	
	public static long[] euclid(long a,long b){
		long r0=a,r1=b,s0=1,s1=0,t0=0,t1=1,q,tmp;
		while(r1!=0){
			q=r0/r1;
			tmp=r1;	r1=r0-q*r1;	r0=tmp;
			tmp=s1;	s1=s0-q*s1;	s0=tmp;
			tmp=t1;	t1=t0-q*t1;	t0=tmp;
		}	return a>0? new long[]{s0,t0}:new long[]{-s0,-t0};
	}
	
	public static long modInverse(long a,long m)
	{	return (euclid(a,m)[0]%m+m)%m;	}
	
	public static boolean fermat(long a,long p)
	{	return modPow(a,p,p)==(a%p);	}
}