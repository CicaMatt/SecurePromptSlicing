import java.util.Scanner;

public class ArrayIndexFetcher {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50}; // Example array; modify as needed.
        
        try {
            System.out.println("Value at the provided index: " + getValueAtIndex(id_sequence));
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }

    public static int getValueAtIndex(int[] id_sequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        
        if (!scanner.hasNextInt()) {
            throw new IllegalArgumentException("Invalid input. Please enter a valid integer.");
        }
        
        int index = scanner.nextInt();
        
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index out of bounds. Valid range is 0 to " + (id_sequence.length - 1) + ".");
        }
        
        return id_sequence[index];
    }
}