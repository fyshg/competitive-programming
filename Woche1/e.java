import java.math.BigInteger;
import java.util.Scanner;

public class e{
	

	public static void main( String[] args) {

		Scanner sc = new Scanner(System.in);

		BigInteger a = sc.nextBigInteger();
		BigInteger b = sc.nextBigInteger();
		BigInteger c = sc.nextBigInteger();
		BigInteger d = sc.nextBigInteger();


		String result = new String("");

		while( !(a.equals(BigInteger.ONE) && b.equals(BigInteger.ZERO) && c.equals(BigInteger.ZERO) && d.equals(BigInteger.ONE))) {

			//System.out.println( a + "    " + b  );
			//System.out.println( c + "    " + d  );
			//System.out.println("");

			if ( (a.compareTo(b) == 0 || a.compareTo(b) == 1)  && (c.compareTo(d) == 0 || c.compareTo(d) == 1)){
				result = result + '0';
				a = a.subtract(b);
				c = c.subtract(d);
			} else {
				result = result + '1';
				b = b.subtract(a);
				d = d.subtract(c);
			}

		}

		String reverse = new StringBuffer(result).reverse().toString();
		System.out.println(reverse);







		sc.close();
	}
}