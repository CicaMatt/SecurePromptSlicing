import java.util.Arrays;

public class SalesCalculator {
    private double[] monthlySales = {15000.0, 21000.0, 18000.0};

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
        System.out.println(totalFirstQuarterSales);
    }
}