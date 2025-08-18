import java.util.Arrays;

public class SalesSum {
    private double[] sales = {150.0, 200.0, 300.0};

    public double getMonthlySales(int month) {
        return sales[month];
    }

    public static void main(String[] args) {
        SalesSum ss = new SalesSum();
        double sum = 0;
        for (int i = 0; i <= 2; i++) {
            sum += ss.getMonthlySales(i);
        }
        System.out.println(sum);
    }
}