import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Example array, replace with your own if needed.
        int[] id_sequence = {10, 20, 30, 40, 50};

        // Read an integer from the standard input
        System.out.print("Enter index: ");
        int index = scanner.nextInt();
        
        // Call getValueFromArray and exit with its return value as the code
        System.exit(getValueFromArray(id_sequence, id_sequence.length, index));
    }

    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        // Return a specific exit code for invalid index
        System.out.println("Index out of bounds");
        return -1;
    }
}