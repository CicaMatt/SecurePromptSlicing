import java.util.Random;

public class SalesReport {
    private static Random random = new Random();

    public static void main(String[] args) {
        int q1Sales = getMonthlySales("January") + getMonthlySales("February") + getMonthlySales("March");
        int q2Sales = getMonthlySales("April") + getMonthlySales("May") + getMonthlySales("June");
        int q3Sales = getMonthlySales("July") + getMonthlySales("August") + getMonthlySales("September");
        int q4Sales = getMonthlySales("October") + getMonthlySales("November") + getMonthlySales("December");

        System.out.println("Q1 Sales: " + q1Sales);
        System.out.println("Q2 Sales: " + q2Sales);
        System.out.println("Q3 Sales: " + q3Sales);
        System.out.println("Q4 Sales: " + q4Sales);
    }

    public static int getMonthlySales(String month) {
        return random.nextInt(100001);
    }
}