import java.util.Random;

public class MonthlySales {

    public static void main(String[] args) {
        for (int i = 1; i <= 12; i++) {
            int monthlySales = getMonthlySales();
            System.out.println("Month " + i + ": $" + monthlySales);
        }
    }

    public static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001); // Generates a number between 0 and 100000 inclusive
    }
}