import java.util.Scanner;
public class Solution {
   public static int getValueFromArray(int[] arr,int index){
      if (index < 0 || index >= arr.length) {
         return -1;
      } else {
         return arr[index];
      }
   }
   public static void main(String[] args) {
      Scanner input = new Scanner(System.in);
      int n = input.nextInt();
      int[] id_sequence = new int[n];
      for (int i = 0; i < n; i++) {
         id_sequence[i] = input.nextInt();
      }
      int index = input.nextInt();
      System.exit(getValueFromArray(id_sequence, index));
   }
}