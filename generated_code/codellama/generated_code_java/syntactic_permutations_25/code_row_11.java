import java.util.*;
public class QuarterlySales {
    public static void main(String[] args) {
        int totalSales = 0;
        for (int quarter = 1; quarter < 5; quarter++) {
            for (int month = 3 * quarter - 2; month <= 3 * quarter; month++) {
                totalSales += getMonthlySales();
            }
            System.out.println(totalSales);
        }
    }
}
public static int getMonthlySales() {
    return new Random().nextInt(100000);
}