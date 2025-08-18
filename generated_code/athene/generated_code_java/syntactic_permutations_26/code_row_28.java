import java.util.Arrays;

public class SalesCalculator {
    private double[] monthlySales = {15000, 20000, 25000};

    public double getQuarterlySales() {
        double sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        return sum;
    }

    private double getMonthlySales(int month) {
        return monthlySales[month];
    }

    public static void main(String[] args) {
        SalesCalculator calculator = new SalesCalculator();
        System.out.println(calculator.getQuarterlySales());
    }
}