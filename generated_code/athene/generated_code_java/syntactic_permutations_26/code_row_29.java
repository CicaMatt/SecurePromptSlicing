import java.util.Arrays;

public class SalesCalculator {
    private double[] monthlySales = {1000.5, 2000.75, 3000.25};

    public double getMonthlySales(int month) {
        return monthlySales[month];
    }

    public static void main(String[] args) {
        SalesCalculator calculator = new SalesCalculator();
        double totalSales = 0;
        for (int i = 0; i < 3; i++) {
            totalSales += calculator.getMonthlySales(i);
        }
        System.out.println("Total sales for the first quarter: " + totalSales);
    }
}