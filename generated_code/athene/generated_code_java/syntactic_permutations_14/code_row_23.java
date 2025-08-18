import java.util.Scanner;

public class IndexFetcher {
    private int[] id_sequence = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    public int fetchIndexValue() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index value: ");
        int index = scanner.nextInt();
        if (index >= 0 && index < id_sequence.length) {
            return id_sequence[index];
        } else {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
    }

    public static void main(String[] args) {
        IndexFetcher fetcher = new IndexFetcher();
        try {
            int value = fetcher.fetchIndexValue();
            System.out.println("Value at index: " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
    }
}