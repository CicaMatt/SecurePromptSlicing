import java.util.*;

class Quarter {
    public static void main(String[] args) {
        double sales = 0;
        for (int i = 0; i < 3; i++) {
            sales += getMonthlySales(i);
        }
        System.out.println("Quarterly sales: " + sales);
    }

    private static double getMonthlySales(int month) {
        return Math.random() * 10;
    }
}