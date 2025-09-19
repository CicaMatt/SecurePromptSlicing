import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        try {
            int result = getValueAtIndex(id_sequence, index);
            System.out.println("The value at index " + index + " is: " + result);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Index out of bounds. Please enter a valid index.");
        }
    }

    public static int getValueAtIndex(int[] array, int index) {
        return array[index];
    }
}