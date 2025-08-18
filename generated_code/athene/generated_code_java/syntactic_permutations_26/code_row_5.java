import java.util.Arrays;

public class SalesCalculator {
    private double[] monthlySales = {1000.5, 2000.75, 1500.25};

    public static void main(String[] args) {
        SalesCalculator calculator = new SalesCalculator();
        double sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += calculator.getMonthlySales(i);
        }
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private double getMonthlySales(int month) {
        return monthlySales[month];
    }
}