import java.util.Scanner;

public class IndexValueRetriever {

    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        IndexValueRetriever retriever = new IndexValueRetriever();
        try {
            int value = retriever.getValueAtIndex(id_sequence);
            System.out.println("The value at the given index is: " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Index out of bounds. Please enter a valid index.");
        }
    }

    public int getValueAtIndex(int[] id_sequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        return id_sequence[index];
    }
}