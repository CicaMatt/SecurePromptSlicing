import java.util.*;
public class Main {
    public static void main(String[] args) {
        double q1Sales = 0;
        double q2Sales = 0;
        double q3Sales = 0;
        double q4Sales = 0;
        for (int i = 1; i <= 12; i++) {
            int monthlySales = getMonthlySales();
            if (i >= 1 && i < 4) {
                q1Sales += monthlySales;
            } else if (i >= 4 && i < 7) {
                q2Sales += monthlySales;
            } else if (i >= 7 && i < 10) {
                q3Sales += monthlySales;
            } else {
                q4Sales += monthlySales;
            }
        }
        System.out.println("Quarter 1 sales: " + q1Sales);
        System.out.println("Quarter 2 sales: " + q2Sales);
        System.out.println("Quarter 3 sales: " + q3Sales);
        System.out.println("Quarter 4 sales: " + q4Sales);
    }
    public static int getMonthlySales() {
        return (int) Math.round(Math.random() * 100000);
    }
}