import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        return -1; // Return -1 or any other error code for invalid indices
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int[] id_sequence = {1, 2, 3, 4, 5}; // Example array, modify as needed
        int size = id_sequence.length;
        
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        
        int result = getValueFromArray(id_sequence, size, index);
        
        System.exit(result); // Exit with the value retrieved or -1 for error
    }
}