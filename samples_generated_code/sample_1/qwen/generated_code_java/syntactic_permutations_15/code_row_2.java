import java.util.Scanner;

public class IndexValueRetriever {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        try {
            int index = getUserIndex();
            int value = getValueAtIndex(id_sequence, index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Error: Index is out of bounds.");
        }
    }

    public static int getUserIndex() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index value: ");
        return scanner.nextInt();
    }

    public static int getValueAtIndex(int[] array, int index) throws ArrayIndexOutOfBoundsException {
        return array[index];
    }
}