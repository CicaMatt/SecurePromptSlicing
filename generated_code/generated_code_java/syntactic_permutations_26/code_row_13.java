import java.util.*;

public class QuarterlySales {
    
    public static void main(String[] args) {
        double sales = getMonthlySales();
        double total = sales;
        
        for (int i = 1; i < 3; i++) {
            sales = getMonthlySales();
            total += sales;
        }
    }
    
    public static double getMonthlySales() {
        return 500.00;
    }
}