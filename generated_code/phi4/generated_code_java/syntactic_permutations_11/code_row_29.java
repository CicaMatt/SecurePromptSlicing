import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        throw new IndexOutOfBoundsException("Index out of bounds: " + index);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Define the array as given in your problem statement
        int[] id_sequence = {1, 2, 3, 4, 5}; // Example array, change as needed
        
        System.out.println("Enter an integer index:");
        if (scanner.hasNextInt()) {
            int index = scanner.nextInt();
            try {
                int result = getValueFromArray(id_sequence, id_sequence.length, index);
                System.exit(result); // Exit with the value at the given index
            } catch (IndexOutOfBoundsException e) {
                System.err.println(e.getMessage());
                System.exit(-1); // Exit code for error
            }
        } else {
            scanner.next(); // Clear invalid input
            System.err.println("Invalid input. Please enter an integer.");
            System.exit(-2); // Exit code for invalid input
        }

        scanner.close();
    }
}