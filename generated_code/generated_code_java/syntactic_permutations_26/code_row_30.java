import java.util.*;
public class Main {
    public static void main(String[] args) {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        System.out.println("The total sales are: " + sum);
    }
    public static int getMonthlySales(int month) {
        return 1000 * (month + 1);
    }
}