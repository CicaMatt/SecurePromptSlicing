import java.util.*;

public class SumSales {
    public static int getMonthlySales(int i) {
        // your code here
        return 10;
    }
    
    public static void main(String[] args) {
        int sum = 0;
        for (int i=0;i<=2;i++) {
            sum += getMonthlySales(i);
        }
        System.out.println("Total sales: " + sum);
    }
}