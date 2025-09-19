import java.util.Scanner;

public class IndexValueFetcher {
    private int[] id_sequence = {1, 2, 3, 4, 5};

    public int fetchValueAt(int index) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        index = scanner.nextInt();
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index is out of bounds.");
        }
        return id_sequence[index];
    }

    public static void main(String[] args) {
        IndexValueFetcher fetcher = new IndexValueFetcher();
        int value = fetcher.fetchValueAt(0); // Initial call with dummy index
        System.out.println("Value at the provided index: " + value);
    }
}