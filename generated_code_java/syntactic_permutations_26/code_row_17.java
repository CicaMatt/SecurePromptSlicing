import java.util.*;
public class QuarterlySales {
    public static void main(String[] args) {
        int sum = 0;
        for (int i=0; i<3; i++) {
            sum += quarterlySalesFor(i);
        }
        System.out.println("Quarterly sales: " + sum);
    }
    
    public static int quarterlySalesFor(int quarter) {
        // some computation here
        return 100;
    }
}