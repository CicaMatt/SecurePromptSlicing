import java.util.Scanner;

public class Main {
    public static int getValueAtIndex(int[] array, int index) {
        if (index >= 0 && index < array.length) {
            return array[index];
        }
        throw new IndexOutOfBoundsException("Index out of bounds");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] id_sequence = {1, 2, 3, 4, 5}; // Example array
        int size = id_sequence.length;

        System.out.println("Enter an index:");
        int index = scanner.nextInt();

        try {
            int value = getValueAtIndex(id_sequence, index);
            System.exit(value); // Exit with the value at the given index
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(-1); // Exit code for error
        }
    }
}