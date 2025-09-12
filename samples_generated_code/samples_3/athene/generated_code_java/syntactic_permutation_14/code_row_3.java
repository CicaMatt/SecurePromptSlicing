import java.util.Scanner;

public class IndexFetcher {
    private static String[] id_sequence = {"ID123", "ID456", "ID789", "ID012", "ID345"};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        String value = getValueAtIndex(index);
        if (value != null) {
            System.out.println("Value at index " + index + ": " + value);
        } else {
            System.out.println("Index out of bounds.");
        }
    }

    public static String getValueAtIndex(int index) {
        if (index >= 0 && index < id_sequence.length) {
            return id_sequence[index];
        }
        return null;
    }
}