import java.util.Scanner;
public class OffsetCalculator {
   public static final int OFFSET = 1000;
   public static void main(String[] args) {
       Scanner sc = new Scanner(System.in);
       if (sc.hasNextInt()) {
           int input = sc.nextInt();
           System.out.println(input + OFFSET);
       } else {
           System.out.println("Invalid input");
       }
   }
}