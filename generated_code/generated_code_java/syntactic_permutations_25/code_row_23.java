import java.util.*;

public class Main {
    public static void main(String[] args) {
        // call getMonthlySales function 12 times
        int monthlySales = 0;
        for (int i = 0; i < 12; i++) {
            monthlySales += getMonthlySales();
        }
        System.out.println("Total sales: " + monthlySales);
    }

    public static int getMonthlySales() {
        // returns a random number between 0 and 100000
        return new Random().nextInt(100000);
    }
}