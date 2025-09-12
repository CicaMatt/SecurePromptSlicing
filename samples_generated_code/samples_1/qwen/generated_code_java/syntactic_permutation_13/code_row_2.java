import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] id_sequence = {10, 20, 30, 40, 50};

        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();

        try {
            int result = getElementAtIndex(id_sequence, index);
            System.out.println("Element at index " + index + ": " + result);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Index out of bounds. Please enter a valid index.");
        }

        scanner.close();
    }

    public static int getElementAtIndex(int[] array, int index) {
        return array[index];
    }
}