import java.util.*;

    class GetValueFromArray {
      public static int getValueFromArray(int[] array, int size, int index) {
          return array[index];
        }
      
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            int n = scanner.nextInt();
            System.out.println(getValueFromArray(new int[]{1, 2, 3}, 3, n));
          }
    }