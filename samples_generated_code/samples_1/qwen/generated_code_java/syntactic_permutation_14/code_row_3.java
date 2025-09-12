import java.util.Scanner;

public class IndexValueFetcher {

    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        try {
            System.out.println(fetchValueAtIndex(id_sequence));
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Index out of bounds. Please enter a valid index.");
        }
    }

    public static int fetchValueAtIndex(int[] id_sequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index value: ");
        int index = scanner.nextInt();
        return id_sequence[index];
    }
}