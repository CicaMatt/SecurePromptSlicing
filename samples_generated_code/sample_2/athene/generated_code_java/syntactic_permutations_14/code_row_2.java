import java.util.Scanner;

public class IndexValueFetcher {
    private static String[] id_sequence = {"id1", "id2", "id3", "id4", "id5"};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index: ");
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