import java.util.Scanner;

public class IndexValueFetcher {

    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        try {
            int index = getUserInput();
            int value = getValueAtIndex(id_sequence, index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Error: Index is out of bounds.");
        }
    }

    public static int getUserInput() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        return scanner.nextInt();
    }

    public static int getValueAtIndex(int[] array, int index) throws IndexOutOfBoundsException {
        if (index < 0 || index >= array.length) {
            throw new IndexOutOfBoundsException();
        }
        return array[index];
    }
}