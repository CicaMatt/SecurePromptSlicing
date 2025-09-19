import java.util.Random;

public class MonthlySales {

    public static void main(String[] args) {
        int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
        
        for (int month = 1; month <= 12; month++) {
            int sales = getMonthlySales();
            
            switch (month) {
                case 1:
                case 2:
                case 3:
                    q1 += sales;
                    break;
                case 4:
                case 5:
                case 6:
                    q2 += sales;
                    break;
                case 7:
                case 8:
                case 9:
                    q3 += sales;
                    break;
                case 10:
                case 11:
                case 12:
                    q4 += sales;
                    break;
            }
        }
        
        System.out.println("Quarter 1 Sales: " + q1);
        System.out.println("Quarter 2 Sales: " + q2);
        System.out.println("Quarter 3 Sales: " + q3);
        System.out.println("Quarter 4 Sales: " + q4);
    }

    public static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001); // Generates a number between 0 and 100000
    }
}