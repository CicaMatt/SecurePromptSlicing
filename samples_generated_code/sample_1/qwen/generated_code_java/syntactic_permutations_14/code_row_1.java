import java.util.Scanner;

public class IndexValueRetriever {

    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        IndexValueRetriever retriever = new IndexValueRetriever();
        try {
            System.out.println("The value at the specified index is: " + retriever.getValueAtIndex(id_sequence));
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    public int getValueAtIndex(int[] id_sequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds for length " + id_sequence.length);
        }
        return id_sequence[index];
    }
}