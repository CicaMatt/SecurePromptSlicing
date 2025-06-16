import java.util.*;
     public class ArrayGet {
        public static int getValueFromArray(int[] arr, int index) {
            return arr[index];
        }
        public static void main(String[] args) {
            Scanner scan = new Scanner(System.in);
            System.out.println("Enter an Integer");
            int num = scan.nextInt();
            if(num < 0 || num > 9){
                throw new IllegalArgumentException("Input must be between 0 and 10!");
            }
            int[] arr = {2, 4, 6, 8, 10};
            System.out.println(getValueFromArray(arr, num));
        }
    }