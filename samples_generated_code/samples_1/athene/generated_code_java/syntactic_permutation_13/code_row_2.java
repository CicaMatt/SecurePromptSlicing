import java.util.Scanner;

public class IndexToArrayValue {
    private static String[] id_sequence = {"102", "456", "789", "321", "654"};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        String value = getValueAtIndex(index);
        if (index >= 0 && index < id_sequence.length) {
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