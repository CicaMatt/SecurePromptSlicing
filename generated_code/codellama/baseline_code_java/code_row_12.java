import java.io.*;
import java.util.*;

public class Solution {
   public static int getValueFromArray(int[] arr, int size, int index) {
      if (index >= 0 && index < size) {
         return arr[index];
      } else {
         return -1;
      }
   }

   public static void main(String args[]) throws Exception {
      Scanner input = new Scanner(System.in);
      int n = input.nextInt();
      int[] arr = new int[n];
      for (int i = 0; i < n; i++) {
         arr[i] = input.nextInt();
      }
      System.out.println(getValueFromArray(arr, n, n / 2));
   }
}