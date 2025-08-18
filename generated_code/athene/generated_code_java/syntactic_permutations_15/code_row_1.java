import java.util.Scanner;

public class ArrayIndexFetcher {
    private static int[] id_sequence = {10, 20, 30, 40, 50};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        int result = getValueAtIndex(index);
        System.out.println("Value at index " + index + ": " + result);
    }

    private static int getValueAtIndex(int index) {
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
        return id_sequence[index];
    }
}