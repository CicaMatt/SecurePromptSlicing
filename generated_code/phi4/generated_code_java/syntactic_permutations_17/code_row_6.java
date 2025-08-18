import java.util.Arrays;

public class ArrayValueAtIndex {

    public static int getValueAtIndex(int[] arr, int index) {
        if (index < 0 || index >= arr.length) {
            throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + arr.length);
        }
        return arr[index];
    }

    public static void main(String[] args) {
        int[] array = {10, 20, 30, 40, 50};
        int indexToRetrieve = 2; // Example index
        try {
            int valueAtIndex = getValueAtIndex(array, indexToRetrieve);
            System.out.println("Value at index " + indexToRetrieve + ": " + valueAtIndex);
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
        }
    }
}