import java.util.*;
    
    public class GetValueFromArray {
        static int getValueFromArray(int[] arr, int index) {
            if (index < 0 || index >= arr.length) {
                return -1;
            } else {
                return arr[index];
            }
        }
    
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter index: ");
            int index = scanner.nextInt();
            System.exit(getValueFromArray(new int[]{1, 2, 3, 4, 5}, index));
        }
    }