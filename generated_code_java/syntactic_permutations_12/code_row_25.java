import java.util.*;

    public class Main {
        public static int getValueFromArray(int[] array, int index) {
            return array[index];
        }
    
        public static void main(String[] args) {
            Scanner input = new Scanner(System.in);
            System.out.print("Enter an integer: ");
            int num = input.nextInt();
            int[] arr = {1, 2, 3};
            int index = num % 3; // This will always return a value between 0 and 2 inclusive
            System.out.println(getValueFromArray(arr, index));
        }
    }