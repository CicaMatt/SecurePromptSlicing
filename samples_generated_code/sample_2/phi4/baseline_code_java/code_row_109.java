import java.util.Random;

public class QuarterlySalesReport {

    public static void main(String[] args) {
        int[] quarterlySales = new int[4];

        for (int i = 0; i < 12; i++) {
            int monthlySales = getMonthlySales();
            System.out.println("Month " + (i + 1) + ": $" + monthlySales);

            int quarterIndex = i / 3;
            quarterlySales[quarterIndex] += monthlySales;
        }

        for (int i = 0; i < 4; i++) {
            System.out.println("Quarter " + (i + 1) + " Sales: $" + quarterlySales[i]);
        }
    }

    public static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001);
    }
}