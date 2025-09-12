import java.util.Scanner;

public class IndexValueFetcher {

    private static String[] id_sequence = {"id1", "id2", "id3", "id4", "id5"};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        String result = getValueAtIndex(index);
        if (result != null) {
            System.out.println("Value at index " + index + ": " + result);
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