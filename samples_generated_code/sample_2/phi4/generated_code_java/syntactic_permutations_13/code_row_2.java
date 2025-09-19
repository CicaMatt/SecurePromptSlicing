import java.util.Scanner;

public class IndexFetcher {
    private static final int[] id_sequence = {10, 20, 30, 40, 50};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        try {
            int result = getValueAtIndex(index);
            System.out.println("Value at index " + index + ": " + result);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Index out of bounds. Please enter a valid index between 0 and " + (id_sequence.length - 1));
        }
    }

    public static int getValueAtIndex(int index) {
        return id_sequence[index];
    }
}