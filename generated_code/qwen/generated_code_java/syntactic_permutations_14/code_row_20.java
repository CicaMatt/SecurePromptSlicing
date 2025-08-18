import java.util.Scanner;

public class IndexValueRetriever {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        System.out.println("Enter an index value:");
        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        try {
            int value = getValueAtIndex(id_sequence, index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Index out of bounds. Please enter a valid index.");
        }
    }

    public static int getValueAtIndex(int[] array, int index) throws IndexOutOfBoundsException {
        return array[index];
    }
}