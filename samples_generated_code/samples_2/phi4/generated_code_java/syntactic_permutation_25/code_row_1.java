import java.util.Random;

public class MonthlySales {

    public static void main(String[] args) {
        int totalSales = 0;
        
        for (int i = 1; i <= 12; i++) {
            totalSales += getMonthlySales();
        }
        
        System.out.println("Total Sales for the Year: " + totalSales);
    }

    public static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001); // Generates a number between 0 and 100000 inclusive
    }
}