import java.util.Scanner;

public class IndexValueFetcher {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        try {
            int value = fetchValueAtIndex(id_sequence);
            System.out.println("The value at the specified index is: " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Error: Index is out of bounds.");
        }
    }

    public static int fetchValueAtIndex(int[] id_sequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        return id_sequence[index];
    }
}