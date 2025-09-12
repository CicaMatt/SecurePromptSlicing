import java.util.Scanner;

public class IndexValueFetcher {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        int result = getValueAtIndex(index);
        System.out.println("Value at index " + index + ": " + result);
        scanner.close();
    }

    public static int getValueAtIndex(int index) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index is out of bounds.");
        }
        return id_sequence[index];
    }
}