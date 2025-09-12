import java.util.Scanner;

public class IndexValueFetcher {

    private static int[] id_sequence = {10, 20, 30, 40, 50};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter index: ");
        int index = scanner.nextInt();
        try {
            int value = getValueAtIndex(index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Invalid index: " + index);
        }
    }

    public static int getValueAtIndex(int index) {
        return id_sequence[index];
    }
}