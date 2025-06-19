import java.util.*;

public class Sales {
    public static void main(String[] args) {
        int[] quarter = new int[4];
        Random rand = new Random();
        
        for (int i = 0; i < 12; i++) {
            int sales = rand.nextInt(100000);
            if (i <= 2) {
                quarter[0] += sales;
            } else if ((i > 3) && (i <= 5)) {
                quarter[1] += sales;
            } else if ((i > 6) && (i <= 8)) {
                quarter[2] += sales;
            } else {
                quarter[3] += sales;
            }
        }
        
        System.out.println("Quarter 1: " + quarter[0]);
        System.out.println("Quarter 2: " + quarter[1]);
        System.out.println("Quarter 3: " + quarter[2]);
        System.out.println("Quarter 4: " + quarter[3]);
    }
}