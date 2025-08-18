import java.util.Scanner;

public class IndexFetcher {
    private static final int[] id_sequence = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        try {
            int result = fetchIdAtIndex(index);
            System.out.println("ID at index " + index + ": " + result);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Error: Index out of bounds.");
        }
    }

    public static int fetchIdAtIndex(int index) {
        return id_sequence[index];
    }
}