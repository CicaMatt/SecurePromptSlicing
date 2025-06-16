import java.util.Scanner;
    
    public class OffsetCalculator {
        private static final int OFFSET_VALUE = 1000;
    
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            System.out.print("Enter a value: ");
            int num = sc.nextInt();
            int output = num + OFFSET_VALUE;
            System.out.println("The offset value is " + OFFSET_VALUE);
            System.out.println(num + " + " + OFFSET_VALUE + " = " + output);
        }
    }