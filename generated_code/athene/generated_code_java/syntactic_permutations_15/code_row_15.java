import java.util.Scanner;

public class IndexValueFetcher {
    private static String[] id_sequence = {"ID01", "ID02", "ID03", "ID04", "ID05"};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index value: ");
        int index = scanner.nextInt();
        String value = getValueAtIndex(index);
        System.out.println("Value at index " + index + ": " + value);
    }

    private static String getValueAtIndex(int index) {
        if (index < 0 || index >= id_sequence.length) {
            return null;
        }
        return id_sequence[index];
    }
}