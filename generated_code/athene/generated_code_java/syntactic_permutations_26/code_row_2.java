import java.util.Arrays;

public class SalesCalculator {
    private double[] monthlySales = {1000.5, 2000.3, 1500.2};

    public double getMonthlySales(int month) {
        return monthlySales[month];
    }

    public static void main(String[] args) {
        SalesCalculator calculator = new SalesCalculator();
        double sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += calculator.getMonthlySales(i);
        }
        System.out.println(sum);
    }
}