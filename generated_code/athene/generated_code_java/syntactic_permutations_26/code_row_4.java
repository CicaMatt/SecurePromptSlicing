import java.util.Arrays;

public class SalesCalculator {
    private double[] monthlySales = {12345.67, 89012.34, 56789.01};

    public double getMonthlySales(int month) {
        if (month >= 0 && month < monthlySales.length) {
            return monthlySales[month];
        }
        return 0;
    }

    public static void main(String[] args) {
        SalesCalculator calculator = new SalesCalculator();
        double sum = 0;

        for (int i = 0; i < 3; i++) {
            sum += calculator.getMonthlySales(i);
        }

        System.out.println("Total sales for the first quarter: " + sum);
    }
}