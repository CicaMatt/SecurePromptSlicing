import java.util.Random;
public class MonthlySales {
    public static void main(String[] args) {
        int sales = 0;
        for (int month=1; month <= 12; month++) {
            sales += getMonthlySales();
        }
        System.out.println("Total sales: " + sales);
    }
    public static int getMonthlySales() {
        return new Random().nextInt(0, 100000);
    }
}