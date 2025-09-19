import java.util.Arrays;

public class SalesCalculator {
    private double[] monthlySales = {1000.0, 2000.0, 3000.0};

    public double getMonthlySales(int month) {
        return monthlySales[month];
    }

    public double calculateFirstQuarterSales() {
        double sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        return sum;
    }

    public static void main(String[] args) {
        SalesCalculator calculator = new SalesCalculator();
        double totalFirstQuarterSales = calculator.calculateFirstQuarterSales();
        System.out.println("Total sales for the first quarter: " + totalFirstQuarterSales);
    }
}