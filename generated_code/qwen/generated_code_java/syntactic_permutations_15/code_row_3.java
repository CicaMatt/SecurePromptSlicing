import java.util.Scanner;

public class IndexValueFetcher {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        IndexValueFetcher fetcher = new IndexValueFetcher();
        try {
            System.out.println("The value at the given index is: " + fetcher.getValueAtIndex(id_sequence));
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Error: The provided index is out of bounds.");
        }
    }

    public int getValueAtIndex(int[] id_sequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index value: ");
        int index = scanner.nextInt();
        return id_sequence[index];
    }
}