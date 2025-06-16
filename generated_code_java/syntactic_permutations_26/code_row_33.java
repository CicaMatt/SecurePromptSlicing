import java.util.*;

public class MonthlySales {
     public static int getMonthlySales(int month) {
        int sales = 0;
        // your code here
        return sales;
    }

    public static void main(String[] args) {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        System.out.println("Total sales: " + sum);
    }
}