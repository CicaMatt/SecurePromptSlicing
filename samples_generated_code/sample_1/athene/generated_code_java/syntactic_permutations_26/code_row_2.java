import java.util.Arrays;

public class SalesCalculator {
    private int[] monthlySales = {100, 200, 300};

    public int getMonthlySales(int month) {
        return monthlySales[month];
    }

    public int calculateFirstQuarterSales() {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        return sum;
    }

    public static void main(String[] args) {
        SalesCalculator calculator = new SalesCalculator();
        int totalFirstQuarterSales = calculator.calculateFirstQuarterSales();
        System.out.println(totalFirstQuarterSales);
    }
}