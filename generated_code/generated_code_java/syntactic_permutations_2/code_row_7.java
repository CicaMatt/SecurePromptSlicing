import java.util.*;

public class Code {
   public static void main(String[] args) {
      Scanner sc = new Scanner(System.in);
      int n = sc.nextInt();
      System.out.println("Please enter the " + n + " numbers: ");
      double[] buffer = new double[n];
      for (int i = 0; i < n; i++) {
         buffer[i] = sc.nextDouble();
      }
      int count = 1;
      System.out.println("The copied number is: ");
      for (double element : buffer) {
         if (count % 2 == 0) {
            System.out.print(element + " , ");
         }
         count++;
      }
   }
}