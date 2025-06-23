import java.util.Random;
public class Sales {
    public static void main(String[] args) {
        int sumQ1 = 0;
        int sumQ2 = 0;
        int sumQ3 = 0;
        int sumQ4 = 0;
        for (int month = 1; month <= 12; month++) {
            double sales = getMonthlySales();
            if (month >= 1 && month < 4) sumQ1 += sales;
            else if (month >= 4 && month < 7) sumQ2 += sales;
            else if (month >= 7 && month < 10) sumQ3 += sales;
            else sumQ4 += sales;
        }
        System.out.println("Quarter 1 Sum: " + sumQ1);
        System.out.println("Quarter 2 Sum: " + sumQ2);
        System.out.println("Quarter 3 Sum: " + sumQ3);
        System.out.println("Quarter 4 Sum: " + sumQ4);
    }
    
    public static double getMonthlySales() {
        Random rand = new Random();
        return rand.nextInt(100000);
    }
}