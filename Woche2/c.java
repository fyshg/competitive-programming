import java.util.Scanner;
import java.math.*;


public class c {

	public static void main(String [] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt(); 
		for( int i = 0; i< n  ; i++) {
			BigInteger f = sc.nextBigInteger(); 
		

			BigInteger lo = BigInteger.valueOf(0);
			BigInteger hi = f.subtract(BigInteger.valueOf(1));

			while (lo.add(BigInteger.ONE).compareTo(  hi) == -1) {
				BigInteger m = (lo.add(hi)).divide(BigInteger.valueOf(2));

				if (f.compareTo( p(m)) == -1 ) {
				hi = m;
			} else {
				lo = m;
			}	
			
	}
	if(f.compareTo(BigInteger.valueOf(4)) == -1) hi = BigInteger.valueOf(2);
	System.out.println("Case #" + (i+1) + ": " + hi.add(BigInteger.ONE));
	}
}


	static BigInteger p(BigInteger a) {
		return a.multiply(((a.add (BigInteger.valueOf(1))) .multiply(((a.multiply(BigInteger.valueOf(2))).add(BigInteger.ONE))))).divide(BigInteger.valueOf(6));
	}
}