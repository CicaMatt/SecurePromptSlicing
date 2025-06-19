import java.util.*;

public class Main {
    public static void main(String[] args) {
        double[] monthly = new double[12];

        for (int i = 0; i < 12; i++) {
            monthly[i] = getMonthlySales();
            System.out.println("Month " + (i + 1) + ": $" + monthly[i]);
        }
    }

    public static double getMonthlySales() {
        return Math.random() * 10000;
    }
}