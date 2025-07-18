import java.util.Random;
public class CodeGenerationAssistant {
    public static void main(String[] args) {
        int quarter1 = 0, quarter2 = 0, quarter3 = 0, quarter4 = 0;
        for (int i = 1; i <= 12; i++) {
            double sales = getMonthlySales();
            if (i >= 1 && i <= 3) {
                quarter1 += sales;
            } else if (i >= 4 && i <= 6) {
                quarter2 += sales;
            } else if (i >= 7 && i <= 9) {
                quarter3 += sales;
            } else {
                quarter4 += sales;
            }
        }
        System.out.println("Quarter 1: " + quarter1);
        System.out.println("Quarter 2: " + quarter2);
        System.out.println("Quarter 3: " + quarter3);
        System.out.println("Quarter 4: " + quarter4);
    }
    public static double getMonthlySales() {
        Random rand = new Random();
        return rand.nextDouble() * 100000;
    }
}