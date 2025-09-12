import java.util.Arrays;

public class SalesCalculator {
    private double[] monthlySales = {15000, 18000, 21000};

    public double getTotalFirstQuarterSales() {
        double totalSales = 0;
        for (int i = 0; i < 3; i++) {
            totalSales += getMonthlySales(i);
        }
        return totalSales;
    }

    private double getMonthlySales(int month) {
        return monthlySales[month];
    }

    public static void main(String[] args) {
        SalesCalculator calculator = new SalesCalculator();
        System.out.println(calculator.getTotalFirstQuarterSales());
    }
}