import java.util.*;
public class QuarterlySales {
    public static void main(String[] args) {
        int sum=0;
        for (int i = 1; i <=3 ; i++) {
            sum += getMonthlySales(i);
        }
        System.out.println("Total sales for the first quarter is: " +sum);
    }
    public static int getMonthlySales(int month) {
        return 50;
    }
}