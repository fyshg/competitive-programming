import java.math.BigDecimal;
import java.math.MathContext;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {

    static class Point {
        BigDecimal x, y;

        public Point(BigDecimal x, BigDecimal y) {
            this.x = x;
            this.y = y;
        }

        public Point add(Point p2) {
            return new Point(this.x.add( p2.x), this.y.add( p2.y));
        }
        public Point multiply(BigDecimal s ) {
            return new Point(this.x.multiply(s), this.y.multiply(s));
        }
        public Point subtract(Point p2) {
            return new Point(this.x.subtract( p2.x), this.y.subtract( p2.y));
        }

    }

    static BigDecimal twoarea(List<Point> poly) {
        int n = poly.size();
        BigDecimal ret = new BigDecimal(0);
        for(int i = 0; i < n; i++) {
            ret = ret.add(   ((poly.get((i+1)%n).x.subtract(poly.get(i).x)  ).multiply(    (poly.get((i+1)%n).y.add(poly.get(i).y))   )   )  );
        }
        return ret.abs().divide(new BigDecimal(2) , MathContext.DECIMAL128);
    }

     static BigDecimal test(List<Point> poly, BigDecimal s) {
        List<Point> newpoly = new ArrayList<>();
        int n = poly.size();
        for (int i = 0; i < n; i++) {
            newpoly.add(( poly.get(i).add( ((poly.get((i+1)%n).subtract(poly.get(i) )    ).multiply((BigDecimal.ONE.divide(s, MathContext.DECIMAL128))) ))));
            if( s.compareTo(new BigDecimal(2)) != 0) newpoly.add((poly.get((i+1)%n).add( ((poly.get(i).subtract(poly.get((i+1)%n))).multiply((BigDecimal.ONE.divide(s, MathContext.DECIMAL128)))))));
        }
        return twoarea(newpoly);
    }

    public static void main(String[] args) {
	// write your code here
        Scanner sc = new Scanner(System.in);
        BigDecimal a = sc.nextBigDecimal();
        int n = sc.nextInt();
        List<Point> poly = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            BigDecimal x = sc.nextBigDecimal();
            BigDecimal y = sc.nextBigDecimal();
            poly.add(new Point(x,y));
        }
        BigDecimal area = a.multiply(twoarea(poly));
        BigDecimal lo = new BigDecimal(2);
        BigDecimal hi = new BigDecimal(1000000000);


        while (lo.compareTo( hi.subtract(new BigDecimal(0.000000000001d))) == -1) {
            BigDecimal mid = (lo.add(hi)).divide(new BigDecimal(2, MathContext.DECIMAL128));

            if (test(poly, mid).compareTo(area) == 1){
                hi = mid;
            }else {
                lo = mid;
            }
        }
        System.out.println(lo);


    }
}
