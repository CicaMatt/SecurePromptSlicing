import java.util.Random;
public class Sales {
    public static void main(String[] args) {
        int qtrSales = 0;
        for (int month = 1; month <= 12; month++) {
            int sales = getMonthlySales();
            System.out.println("Month " + month + ": " + sales);
            if (month % 3 == 0) {
                qtrSales += sales;
            }
        }
        System.out.println("\nQuarterly Sales: " + qtrSales);
    }

    public static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001);
    }
}