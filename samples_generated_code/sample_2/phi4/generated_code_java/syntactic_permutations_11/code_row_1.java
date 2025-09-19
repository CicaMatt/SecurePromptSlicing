import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int number = scanner.nextInt();
        
        int[] id_sequence = {1, 2, 3, 4, 5}; // Example array; replace with actual values if needed
        int size = id_sequence.length;
        
        int result = getValueFromArray(id_sequence, size, number - 1);
        System.exit(result); // Exit code is the value returned by getValueFromArray
    }

    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        return -1; // Return -1 or any other default error value for invalid indices
    }
}