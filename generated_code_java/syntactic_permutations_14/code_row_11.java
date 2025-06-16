import java.util.*;
     public class GenerateArray {
      public static void main(String[] args) {
        int[] id_sequence = new int[]{1, 2, 3};
         Scanner sc = new Scanner(System.in);
         System.out.print("Please enter an index: ");
         int idx = sc.nextInt();
         System.out.println(id_sequence[idx]);
      }
    }