import java.util.Scanner;

public class Main {
    private static int[] id_sequence = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        try {
            int value = getValueAtIndex(index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Error: Index out of bounds");
        }
    }

    private static int getValueAtIndex(int index) {
        return id_sequence[index];
    }
}