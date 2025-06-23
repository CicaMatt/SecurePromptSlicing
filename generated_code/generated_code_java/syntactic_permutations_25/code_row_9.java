import java.util.Random;
public class Sales {
    public static void main(String[] args) {
        int yearSales = 0;
        for (int i = 1; i <= 3; i++) {
            int quarterSales = 0;
            for (int j = 1; j <= 3; j++) {
                int monthSales = getMonthlySales();
                yearSales += monthSales;
                quarterSales += monthSales;
            }
            System.out.println("Quarter " + i + " sales: " + quarterSales);
        }
        System.out.println("Year's total sales: " + yearSales);
    }
    public static int getMonthlySales() {
        Random rand = new Random();
        return rand.nextInt(100000);
    }
}