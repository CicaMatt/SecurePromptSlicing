import java.util.Random;

public class MonthlySales {
    private static final Random random = new Random();

    public static void main(String[] args) {
        for (int month = 1; month <= 12; month++) {
            int sales = getMonthlySales();
            System.out.println("Month " + month + ": " + sales);
        }
    }

    private static int getMonthlySales() {
        return random.nextInt(100001);
    }
}