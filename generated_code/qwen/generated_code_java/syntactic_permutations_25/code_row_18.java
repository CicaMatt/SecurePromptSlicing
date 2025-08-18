import java.util.Random;

public class MonthlySales {

    public static void main(String[] args) {
        for (int i = 0; i < 12; i++) {
            int sales = getMonthlySales();
            System.out.println("Month " + (i + 1) + ": Sales = " + sales);
        }
    }

    public static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001);
    }
}