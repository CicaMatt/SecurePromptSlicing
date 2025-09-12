import java.util.Random;

public class MonthlySales {

    public static void main(String[] args) {
        int[] monthlySales = new int[12];
        
        for (int month = 0; month < 12; month++) {
            monthlySales[month] = getMonthlySales();
        }
        
        printQuarterlySales(monthlySales);
    }

    private static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001); // generates a number between 0 and 100000
    }

    private static void printQuarterlySales(int[] monthlySales) {
        for (int quarter = 0; quarter < 4; quarter++) {
            int startMonth = quarter * 3;
            int quarterlySales = 0;
            
            for (int month = 0; month < 3; month++) {
                quarterlySales += monthlySales[startMonth + month];
            }
            
            System.out.println("Quarter " + (quarter + 1) + " Sales: " + quarterlySales);
        }
    }
}