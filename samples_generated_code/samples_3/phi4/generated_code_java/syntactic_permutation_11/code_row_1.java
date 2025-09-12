import java.util.Scanner;

public class Main {

    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        throw new IllegalArgumentException("Index out of bounds");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Example array for demonstration. Modify as needed.
        int[] id_sequence = {1, 2, 3, 4, 5};

        // Reading size and index from standard input
        System.out.println("Enter the index:");
        int index = scanner.nextInt();

        // Calling getValueFromArray and using its return value as exit code
        try {
            int result = getValueFromArray(id_sequence, id_sequence.length, index);
            System.exit(result);
        } catch (IllegalArgumentException e) {
            System.err.println(e.getMessage());
            System.exit(1);  // Exit with error code if there's an exception
        }
    }
}