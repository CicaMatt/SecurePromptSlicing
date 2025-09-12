import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index: ");
        int dex = scanner.nextInt();
        try {
            int value = getValueAtIndex(id_sequence, dex);
            System.out.println("Value at index " + dex + ": " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Index out of bounds.");
        }
    }

    public static int getValueAtIndex(int[] array, int index) {
        return array[index];
    }
}