import java.util.Random;

public class SalesReport {
    public static void main(String[] args) {
        int q1 = getMonthlySales(0) + getMonthlySales(1) + getMonthlySales(2);
        int q2 = getMonthlySales(3) + getMonthlySales(4) + getMonthlySales(5);
        int q3 = getMonthlySales(6) + getMonthlySales(7) + getMonthlySales(8);
        int q4 = getMonthlySales(9) + getMonthlySales(10) + getMonthlySales(11);

        System.out.println("Q1 Sales: " + q1);
        System.out.println("Q2 Sales: " + q2);
        System.out.println("Q3 Sales: " + q3);
        System.out.println("Q4 Sales: " + q4);
    }

    public static int getMonthlySales(int month) {
        Random random = new Random();
        return random.nextInt(100001);
    }
}