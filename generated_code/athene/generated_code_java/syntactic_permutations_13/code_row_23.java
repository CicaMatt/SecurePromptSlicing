import java.util.Scanner;

public class IndexFetcher {
    private static int[] id_sequence = {10, 20, 30, 40, 50};

    public static int fetchValueAt(int index) {
        if (index < 0 || index >= id_sequence.length) {
            return -1; // Return -1 for invalid indices
        }
        return id_sequence[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        int result = fetchValueAt(index);
        if (result == -1) {
            System.out.println("Invalid index.");
        } else {
            System.out.println("Value at index " + index + ": " + result);
        }
        scanner.close();
    }
}