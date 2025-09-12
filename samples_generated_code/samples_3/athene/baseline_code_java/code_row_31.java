import java.util.Scanner;

public class IndexValueFetcher {
    private int[] id_sequence = {1, 2, 3, 4, 5};

    public int fetchValueAtindex() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter index value: ");
        int index = scanner.nextInt();
        if (index < 0 || index >= id_sequence.length) {
            throw new ArrayIndexOutOfBoundsException("Index out of bounds");
        }
        return id_sequence[index];
    }

    public static void main(String[] args) {
        IndexValueFetcher fetcher = new IndexValueFetcher();
        try {
            int value = fetcher.fetchValueAtindex();
            System.out.println("Value at index: " + value);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
    }
}