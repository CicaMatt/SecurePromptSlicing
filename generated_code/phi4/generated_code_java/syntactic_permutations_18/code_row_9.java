import java.util.Arrays;

public class ArrayValueAtIndex {

    public static void main(String[] args) {
        int number = 5; // Example input
        int[] array = {10, 20, 30, 40, 50, 60, 70}; // Example array

        try {
            int value = getValueAtIndex(array, number);
            System.out.println("Value at index " + number + ": " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Error: Index out of bounds.");
        }
    }

    public static int getValueAtIndex(int[] array, int index) throws IndexOutOfBoundsException {
        return array[index];
    }
}