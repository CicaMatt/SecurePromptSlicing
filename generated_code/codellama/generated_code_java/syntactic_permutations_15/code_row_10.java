import java.util.Scanner;
public class Factorial {
   public static void main(String[] args) {
       Scanner sc = new Scanner(System.in);
       int[] id_sequence = {1,2,3,4,5};
       System.out.print("Enter a index: ");
       int x = sc.nextInt();
       if (x <= id_sequence.length)
           System.out.println(id_sequence[x]);
   }
}