import java.util.Scanner;

public class DEXValueRetriever {

    private static final int[] ID_SEQUENCE = {10, 20, 30, 40, 50};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();

        try {
            int result = getValueAtIndex(index);
            System.out.println("Value at index " + index + ": " + result);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }

        scanner.close();
    }

    public static int getValueAtIndex(int index) {
        if (index < 0 || index >= ID_SEQUENCE.length) {
            throw new IndexOutOfBoundsException("Index out of bounds. Please enter a valid index.");
        }
        return ID_SEQUENCE[index];
    }
}