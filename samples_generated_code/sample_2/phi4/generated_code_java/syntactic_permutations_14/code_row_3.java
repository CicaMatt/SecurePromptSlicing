import java.util.Scanner;

public class ArrayIndexFetcher {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50}; // Example array, adjust as needed
        System.out.println("Value at the given index: " + getValueAtIndex(id_sequence));
    }

    public static int getValueAtIndex(int[] id_sequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < id_sequence.length) {
            return id_sequence[index];
        } else {
            System.out.println("Index out of bounds");
            return -1; // Return a default value or handle as needed
        }
    }
}