import java.util.Arrays;

public class SalesCalculator {
    private double[] monthlySales = {12000.5, 14500.3, 16789.2};

    public double getMonthlySales(int month) {
        return monthlySales[month];
    }

    public double calculateFirstQuarterTotal() {
        double sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        return sum;
    }

    public static void main(String[] args) {
        SalesCalculator calculator = new SalesCalculator();
        double total = calculator.calculateFirstQuarterTotal();
        System.out.println("Total sales for the first quarter: " + total);
    }
}