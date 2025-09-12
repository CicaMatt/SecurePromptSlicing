import java.util.Scanner;

public class IndexFetcher {
    private static int[] id_sequence = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    public static int getValueAtIndex(int index) {
        if (index < 0 || index >= id_sequence.length) {
            return -1;
        }
        return id_sequence[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        int value = getValueAtIndex(index);
        if (value == -1) {
            System.out.println("Index out of bounds.");
        } else {
            System.out.println("Value at index " + index + ": " + value);
        }
        scanner.close();
    }
}