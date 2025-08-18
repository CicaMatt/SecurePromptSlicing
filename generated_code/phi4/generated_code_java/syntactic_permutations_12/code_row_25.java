import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int n = scanner.nextInt();
        int index = scanner.nextInt();

        // Example array; this should be replaced with actual input or data as needed.
        int[] arr = {1, 2, 3, 4, 5}; // Example array for demonstration purposes

        int result = getValueFromArray(arr, arr.length, index);
        
        System.exit(result);
    }

    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        } else {
            throw new IndexOutOfBoundsException("Index out of bounds: " + index);
        }
    }
}