import java.util.Scanner;

public class IndexValueFetcher {
    private int[] id_sequence;

    public IndexValueFetcher(int[] sequence) {
        this.id_sequence = sequence;
    }

    public int fetchValueAtIndex() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index value: ");
        int index = scanner.nextInt();
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index is out of bounds");
        }
        return id_sequence[index];
    }

    public static void main(String[] args) {
        int[] sequence = {1, 2, 3, 4, 5};
        IndexValueFetcher fetcher = new IndexValueFetcher(sequence);
        try {
            int value = fetcher.fetchValueAtIndex();
            System.out.println("Value at index: " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
    }
}