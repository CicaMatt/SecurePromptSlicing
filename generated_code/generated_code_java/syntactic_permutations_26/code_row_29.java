import java.util.*;
public class Main {
    public static void main(String[] args) {
        double total = 0.0;
        for (int i = 0; i < 3; i++) {
            total += getMonthlySales(i);
        }
        
    }
    
    private static double getMonthlySales(int month) {
        return 12.3 * month;
    }
}