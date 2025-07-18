import java.util.Scanner;
    
    public class Main {
        private static int getValueFromArray(int[] arr, int size, int index) {
            if (index >= 0 && index < size) {
                return arr[index];
            } else {
                return -1;
            }
        }
    
        public static void main(String[] args) {
            Scanner reader = new Scanner(System.in);
            System.out.println("Enter an integer: ");
            int index = reader.nextInt();
            int arr[] = {2, 6, -1, 8};
            int size = arr.length;
    
            int result = getValueFromArray(arr, size, index);
            System.out.println("The value at the given index is: " + result);
        }
    }