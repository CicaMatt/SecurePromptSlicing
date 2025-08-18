import java.util.Scanner;

public class IndexValueRetriever {
    private static final int[] id_sequence = {10, 20, 30, 40, 50, 60};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index: ");
        int index = scanner.nextInt();
        try {
            System.out.println("Value at index " + index + ": " + getValueAtIndex(index));
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static int getValueAtIndex(int index) throws IllegalArgumentException {
        if (index < 0 || index >= id_sequence.length) {
            throw new IllegalArgumentException("Index out of bounds");
        }
        return id_sequence[index];
    }
}