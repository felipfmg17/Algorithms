import java.util.*;

class Numbers
{
	// returns a mod m
	public static long mod(long a,long m)
	{	a%=m;	return a>=0?a:a+m;	}
	
	/*	returns gcd(a,b)
		Conditions:
		a != 0	*/
	public static long gcd(long a,long b){
		for(long t;b!=0;)
		{t=b;	b=a%b;	a=t;}
		return Math.abs(a);
	}
	
	/*	returns lcm(a,b)
		Conditions:
		--- gcd(long a,long b):long	*/
	public static long lcm(long a,long b)
	{	return (a*b)/gcd(a,b);	}
	
	// returns 	(b^x) mod m
	public static long modPow(long b,long x,long m){
		long mask=1<<62,res=1;
		for(;mask!=0;mask>>>=1){
			res=(res*res)%m;
			if((x&mask)!=0)
				res=(res*b)%m;
		}	return res;
	}
	
	/*	returns primes<n	*/
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
	
	/* returns a set with prime numbers*/
	public static SortedSet<Long> primes(boolean[] sieve){
		SortedSet<Long> s=new TreeSet<Long>();
		for(int i=0;i<sieve.length;i++)
			if(sieve[i]==true) s.add((long)i);
		return s;
	}
		
	/* returns a  map with de factorization of n */
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
	
	/* returns phi euler totient function of n) */
	public static long phi(long n,SortedSet<Long> primes){
		long res=n;
		for(long p : primes)
			if(p>n)	break;
			else if(n%p==0)
			{res/=p;	res*=p-1;}
		return res;
	}
	
	/* returns s,t such that as+bt=gcd(a,b) */
	public static long[] euclid(long a,long b){
		long r0=a,r1=b,s0=1,s1=0,t0=0,t1=1,q,tmp;
		while(r1!=0){
			q=r0/r1;
			tmp=r1;	r1=r0-q*r1;	r0=tmp;
			tmp=s1;	s1=s0-q*s1;	s0=tmp;
			tmp=t1;	t1=t0-q*t1;	t0=tmp;
		}	return a>0? new long[]{s0,t0}:new long[]{-s0,-t0};
	}
	
	/* returns x such that ax = 1 mod m
		conditions:
		gcd(a,m)=1
		--- euclid(long a,long b):long
	*/
	public static long modInverse(long a,long m)
	{	return (euclid(a,m)[0]%m+m)%m;	}
	
	/*	return true if  a^p = a mod p
		conditions:
		--- modPow(long a,long x,long m):long	*/
	public static boolean fermat(long a,long p)
	{	return modPow(a,p,p)==(a%p);	}
	
	/* 	returns (a)(a+1)(a+2)...(b)	 mod  m  */
	public static long product(long a,long b,long m){
		long res=1;
		for(long i=a;i<=b;i++)
			res=res*i%m;
		return res;
	}
	
	/* 	returns n! mod m 
		conditions:
		---product(long a,long b,long m):long	*/
	public static long factorial(long n,long m)
	{ 	return product(2,n,m);}
	
	
	/* 	returns nPr mod m 
		conditions:
		---product(long a,long b,long m):long	*/
	public static long permutations(long n,long r,long m){
		return product(n-r+1,n,m);
	}
	
	/* 	returns nCr mod m 
		conditions:
		---product(long a,long b,long m):long
		---modInverse(long a,long m):long	*/
	public static long binomial(long n,long r,long m){
		r=Math.min(n-r,r);
		return product(n-r+1,n,m)*modInverse(product(2,r,m),m)%m;
	}
	
	
}