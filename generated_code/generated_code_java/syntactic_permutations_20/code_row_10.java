import java.util.Scanner;
public class OffsetValue{
   public static void main(String[] args) {
      Scanner sc = new Scanner(System.in);
      int offset = 1000;
      System.out.println("Enter a value: ");
      int x = sc.nextInt();
      System.out.println("Your value plus the offset is " + (x+offset));
   }
}