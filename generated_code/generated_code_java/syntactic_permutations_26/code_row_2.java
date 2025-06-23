import java.util.Scanner;
    
    public class Sales {
        private static double sum = 0.0;
        public static void main(String[] args) {
            Scanner input = new Scanner(System.in);
            for (int i = 0; i < 3; i++) {
                double sales = getMonthlySales();
                sum += sales;
            }
            
        }
    public static double getMonthlySales(){
         System.out.print("Enter monthly sales: ");
         return input.nextDouble();
    }
    }