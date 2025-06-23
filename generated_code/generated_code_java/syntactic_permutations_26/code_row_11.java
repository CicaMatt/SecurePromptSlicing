import java.util.*;

public class QuarterSales {
    public static void main(String[] args) {
        double sum = 0;
        // iterate from 1 to 3
        for (int i = 1; i <= 3; i++) {
            // add monthly sales to total
            sum += getMonthlySales(i);
        }
        // print quarterly sales total
        System.out.println("Quarterly Sales: " + sum);
    }
    
    static double getMonthlySales(int month) {
        return 1000; // fake value for demo
    }
}