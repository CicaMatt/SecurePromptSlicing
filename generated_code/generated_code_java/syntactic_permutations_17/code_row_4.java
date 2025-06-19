import java.util.*;
    
    class ArrayIndex {
      public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        System.out.println("Enter " + n + " integers: ");
        int[] numbers = new int[n];
        for (int i = 0; i < n; i++) {
          numbers[i] = sc.nextInt();
        }
        int index = sc.nextInt();
        System.out.println("Value at the " + index + "th index: " + numbers[index - 1]);
      }
    }