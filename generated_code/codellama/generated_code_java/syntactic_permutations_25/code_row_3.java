import java.util.Random;

public class Main {

    public static void main(String[] args) {
        int sales = 0;

        for (int month = 1; month <= 12; month++) {
            sales += getMonthlySales();
            if (month % 3 == 0) {
                System.out.println("Quarter " + month / 3 + ": " + sales);
                sales = 0;
            }
        }
    }

    public static int getMonthlySales() {
        return new Random().nextInt(100000);
    }
}