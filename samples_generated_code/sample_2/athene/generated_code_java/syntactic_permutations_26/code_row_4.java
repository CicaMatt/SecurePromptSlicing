import java.util.Arrays;

public class SalesCalculator {
    private double[] monthlySales = {12000.0, 15000.0, 18000.0};

    public double getMonthlySales(int month) {
        return monthlySales[month];
    }

    public static void main(String[] args) {
        SalesCalculator calculator = new SalesCalculator();
        double sum = 0.0;
        for (int i = 0; i < 3; i++) {
            sum += calculator.getMonthlySales(i);
        }
        System.out.println("Total sales for the first quarter: " + sum);
    }
}