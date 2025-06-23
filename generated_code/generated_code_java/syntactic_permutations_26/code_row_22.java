import java.util.ArrayList;

public class Months {
    public static int getMonthlySales(int month) {
        // Your code here
    }

    public static void main(String[] args) {
        int sum = 0;
        for (int i=0; i <=2 ;i++) {
            sum += Months.getMonthlySales(i);
        }
        System.out.println("Total Sales: " + sum);
    }
}