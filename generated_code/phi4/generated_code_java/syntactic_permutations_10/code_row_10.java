import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        } else {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int[] id_sequence = {1, 2, 3, 4, 5}; // Example array
        System.out.println("Enter an index: ");
        int index = scanner.nextInt();

        try {
            int result = getValueFromArray(id_sequence, id_sequence.length, index);
            System.exit(result); // Exit the program with the return value as exit code
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(1); // Exit with error code 1 if exception occurs
        }
    }
}