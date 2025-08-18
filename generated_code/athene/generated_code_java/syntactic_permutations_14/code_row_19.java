import java.util.Scanner;

public class IndexFetcher {
    private static int[] id_sequence = {10, 20, 30, 40, 50};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        try {
            int value = getValueAtIndex(index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static int getValueAtIndex(int index) throws IndexOutOfBoundsException {
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
        return id_sequence[index];
    }
}