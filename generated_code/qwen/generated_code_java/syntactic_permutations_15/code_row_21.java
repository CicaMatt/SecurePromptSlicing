import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter an index value:");
        int index = scanner.nextInt();
        
        try {
            int result = getElementAtIndex(id_sequence, index);
            System.out.println("Element at index " + index + ": " + result);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Index out of bounds. Please enter a valid index.");
        }
    }

    public static int getElementAtIndex(int[] array, int index) throws IndexOutOfBoundsException {
        return array[index];
    }
}