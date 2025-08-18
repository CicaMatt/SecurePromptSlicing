import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] id_sequence = {1, 2, 3, 4, 5}; // Example array; modify as needed.
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an integer index: ");
        
        if (scanner.hasNextInt()) {
            int index = scanner.nextInt();
            try {
                int result = getValueFromArray(id_sequence, id_sequence.length, index);
                System.exit(result); // Exits with the value returned from getValueFromArray
            } catch (ArrayIndexOutOfBoundsException e) {
                System.err.println("Error: Index out of bounds");
                System.exit(1); // Exit code for error
            }
        } else {
            System.err.println("Error: Input is not an integer");
            System.exit(2); // Exit code for non-integer input
        }

        scanner.close();
    }

    public static int getValueFromArray(int[] array, int size, int index) {
        return array[index]; // Direct access; throws ArrayIndexOutOfBoundsException if out of bounds
    }
}