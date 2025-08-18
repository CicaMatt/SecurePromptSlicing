import java.util.Arrays;

public class SalesCalculator {
    private double[] monthlySales = {150.0, 200.0, 300.0};

    public double getMonthlySales(int month) {
        return monthlySales[month];
    }

    public double calculateTotalSales() {
        double sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        return sum;
    }

    public static void main(String[] args) {
        SalesCalculator calculator = new SalesCalculator();
        double totalSales = calculator.calculateTotalSales();
        System.out.println(totalSales);
    }
}