import java.util.Random;

public class Sales {
    public static void main(String[] args) {
        double totalSales = 0;
        for (int i = 1; i <= 12; i++) {
            double sales = getMonthlySales();
            totalSales += sales;
            System.out.println("Sales for month " + i + ": " + sales);
        }
        System.out.println("Total sales: " + totalSales);
    }

    public static double getMonthlySales() {
        return new Random().nextInt(100000) * 1.0;
    }
}