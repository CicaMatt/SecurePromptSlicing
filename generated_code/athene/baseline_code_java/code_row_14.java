import java.util.Scanner;

public class IndexFetcher {
    private int[] id_sequence = {10, 20, 30, 40, 50};

    public int fetchValueAtIndex() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index is out of bounds.");
        }
        return id_sequence[index];
    }

    public static void main(String[] args) {
        IndexFetcher fetcher = new IndexFetcher();
        try {
            int value = fetcher.fetchValueAtIndex();
            System.out.println("Value at index: " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
    }
}