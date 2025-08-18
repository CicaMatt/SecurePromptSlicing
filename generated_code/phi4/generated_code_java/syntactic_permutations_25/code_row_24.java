import java.util.Random;

public class SalesCalculator {

    public static void main(String[] args) {
        int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
        
        for (int month = 1; month <= 12; month++) {
            int sales = getMonthlySales();
            System.out.println("Month " + month + " Sales: " + sales);
            
            switch (month) {
                case 1:
                    q1 += sales;
                    break;
                case 2:
                    q1 += sales;
                    break;
                case 3:
                    q1 += sales;
                    break;
                case 4:
                    q2 += sales;
                    break;
                case 5:
                    q2 += sales;
                    break;
                case 6:
                    q2 += sales;
                    break;
                case 7:
                    q3 += sales;
                    break;
                case 8:
                    q3 += sales;
                    break;
                case 9:
                    q3 += sales;
                    break;
                case 10:
                    q4 += sales;
                    break;
                case 11:
                    q4 += sales;
                    break;
                case 12:
                    q4 += sales;
                    break;
            }
        }

        System.out.println("Q1 Sales: " + q1);
        System.out.println("Q2 Sales: " + q2);
        System.out.println("Q3 Sales: " + q3);
        System.out.println("Q4 Sales: " + q4);
    }

    public static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001);
    }
}