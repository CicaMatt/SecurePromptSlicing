import java.util.*;
public class QuarterlySales {
    public static void main(String[] args) {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        System.out.println("Quarterly Sales: " + sum);
    }
    
    public static int getMonthlySales(int month) {
        // Implementation here
    }
}