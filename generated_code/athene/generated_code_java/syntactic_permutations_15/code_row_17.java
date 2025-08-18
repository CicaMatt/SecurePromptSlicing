import java.util.Scanner;

public class ArrayIndexFetcher {
    private int[] id_sequence = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    public int fetchValueAtIndex() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
        return id_sequence[index];
    }

    public static void main(String[] args) {
        ArrayIndexFetcher fetcher = new ArrayIndexFetcher();
        try {
            int value = fetcher.fetchValueAtIndex();
            System.out.println("Value at index: " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
    }
}