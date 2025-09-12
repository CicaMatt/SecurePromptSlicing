import java.util.ArrayList;
import java.util.List;

public class SalesCalculator {
    
    public static void main(String[] args) {
        int sum = 0;
        
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        
        System.out.println("Total sales for the first quarter: " + sum);
    }

    public static int getMonthlySales(int month) {
        List<Integer> monthlySalesData = new ArrayList<>();
        monthlySalesData.add(1000); // Example data for January
        monthlySalesData.add(1500); // Example data for February
        monthlySalesData.add(1200); // Example data for March
        
        return monthlySalesData.get(month);
    }
}