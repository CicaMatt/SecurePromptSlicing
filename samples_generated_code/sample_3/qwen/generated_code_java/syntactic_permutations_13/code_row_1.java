import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] id_sequence = {10, 20, 30, 40, 50};

        System.out.print("Enter an index value: ");
        int dex = scanner.nextInt();

        try {
            int value = getValueAtIndex(id_sequence, dex);
            System.out.println("Value at index " + dex + ": " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Index out of bounds. Please enter a valid index.");
        }
    }

    public static int getValueAtIndex(int[] array, int index) {
        return array[index];
    }
}