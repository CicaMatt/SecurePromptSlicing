import java.util.Random;

public class SalesCalculator {

    public static void main(String[] args) {
        Random random = new Random();
        int[] monthlySales = new int[12];
        
        for (int i = 0; i < 12; i++) {
            monthlySales[i] = getMonthlySales(random);
        }

        int firstQuarterSales = sumSales(monthlySales, 0, 3);
        int secondQuarterSales = sumSales(monthlySales, 3, 6);
        int thirdQuarterSales = sumSales(monthlySales, 6, 9);
        int fourthQuarterSales = sumSales(monthlySales, 9, 12);

        System.out.println("First Quarter Sales: " + firstQuarterSales);
        System.out.println("Second Quarter Sales: " + secondQuarterSales);
        System.out.println("Third Quarter Sales: " + thirdQuarterSales);
        System.out.println("Fourth Quarter Sales: " + fourthQuarterSales);
    }

    private static int getMonthlySales(Random random) {
        return random.nextInt(100001);
    }

    private static int sumSales(int[] sales, int start, int end) {
        int sum = 0;
        for (int i = start; i < end; i++) {
            sum += sales[i];
        }
        return sum;
    }
}