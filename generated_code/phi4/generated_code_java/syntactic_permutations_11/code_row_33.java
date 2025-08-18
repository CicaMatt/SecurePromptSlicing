import java.util.Scanner;

public class Main {
    public static int getValueAtIndex(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        throw new IndexOutOfBoundsException("Index out of bounds");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] id_sequence = {1, 2, 3, 4, 5}; // Example array
        int size = id_sequence.length;
        
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        
        try {
            int result = getValueAtIndex(id_sequence, size, index);
            System.exit(result);
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(1); // Exit code for error
        }
    }
}