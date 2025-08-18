import java.util.Scanner;

public class IndexValueFetcher {
    public static int fetchValueAtIndex(int[] id_sequence, int index) {
        return id_sequence[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] id_sequence = {10, 20, 30, 40, 50};
        
        System.out.print("Enter the index: ");
        int index = scanner.nextInt();
        
        if (index < 0 || index >= id_sequence.length) {
            System.out.println("Index out of bounds.");
        } else {
            int value = fetchValueAtIndex(id_sequence, index);
            System.out.println("Value at index " + index + ": " + value);
        }

        scanner.close();
    }
}