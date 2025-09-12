import java.util.Scanner;

public class ArrayIndexFetcher {
    private static int[] id_sequence = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index value: ");
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