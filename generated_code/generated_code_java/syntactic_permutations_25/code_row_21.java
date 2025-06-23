import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec, qu1, qu2, qu3, qu4;
        jan = getMonthlySales();
        feb = getMonthlySales();
        mar = getMonthlySales();
        apr = getMonthlySales();
        may = getMonthlySales();
        jun = getMonthlySales();
        jul = getMonthlySales();
        aug = getMonthlySales();
        sep = getMonthlySales();
        oct = getMonthlySales();
        nov = getMonthlySales();
        dec = getMonthlySales();
        qu1 = jan + feb + mar;
        qu2 = apr + may + jun;
        qu3 = jul + aug + sep;
        qu4 = oct + nov + dec;
        System.out.println(qu1);
        System.out.println(qu2);
        System.out.println(qu3);
        System.out.println(qu4);
    }
    public static int getMonthlySales() {
        return (int) (Math.random() * 100000);
    }
}