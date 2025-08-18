import java.util.Arrays;

public class QuarterlySales {
    private double[] monthlySales = {15000.0, 20000.0, 25000.0};

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
        QuarterlySales qs = new QuarterlySales();
        System.out.println(qs.calculateFirstQuarterTotal());
    }
}