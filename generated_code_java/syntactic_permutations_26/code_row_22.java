import java.util.*;
class TotalQuarterSales {
    public static void main(String[] args) {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        System.out.println("The total quarter sales are: " + sum);
    }
    
    public static int getMonthlySales(int month) {
        // Replace with some real code...
        return 1000;
    }
}