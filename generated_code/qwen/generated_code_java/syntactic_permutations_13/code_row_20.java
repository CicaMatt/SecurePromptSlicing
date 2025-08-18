import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter an index:");
        int index = scanner.nextInt();
        try {
            int value = getValueAtIndex(index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Index out of bounds.");
        }
    }

    public static int getValueAtIndex(int index) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        return id_sequence[index];
    }
}