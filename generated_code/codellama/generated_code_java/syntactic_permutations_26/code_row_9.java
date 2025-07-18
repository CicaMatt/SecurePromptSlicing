import java.util.*;

public class Main {
    
    public static int getMonthlySales(int i) {
        return 0;
    }

    public static void main(String[] args) {
        
        int sum = 0,i=1;
        for (;i<=3;i++) {
            sum += getMonthlySales(i);
        }
        System.out.println(sum);
    }
}