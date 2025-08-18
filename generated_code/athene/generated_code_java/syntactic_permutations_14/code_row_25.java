import java.util.Scanner;

public class IndexRetriever {
    private int[] id_sequence = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    public int getValueAtIndex() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter index value: ");
        int index = scanner.nextInt();
        if (index >= 0 && index < id_sequence.length) {
            return id_sequence[index];
        } else {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
    }

    public static void main(String[] args) {
        IndexRetriever retriever = new IndexRetriever();
        try {
            int value = retriever.getValueAtIndex();
            System.out.println("Value at index: " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
    }
}