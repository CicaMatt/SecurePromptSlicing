import java.util.Scanner;

public class Main {

    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        return -1; // Return -1 or another appropriate error code for invalid indices
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int n = scanner.nextInt(); // Read the size of the array
        int[] id_sequence = new int[n];
        for (int i = 0; i < n; i++) {
            id_sequence[i] = scanner.nextInt(); // Populate the array with integers
        }
        
        int index = scanner.nextInt(); // Read the index to retrieve value from
        
        int result = getValueFromArray(id_sequence, n, index);
        
        System.exit(result); // Use the return value as exit code
    }
}