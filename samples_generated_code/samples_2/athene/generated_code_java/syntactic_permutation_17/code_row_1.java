import java.util.Arrays;

public class ArrayValueFetcher {
    public static int getValueAtIndex(int[] array, int index) {
        if (index < 0 || index >= array.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds for length " + array.length);
        }
        return array[index];
    }

    public static void main(String[] args) {
        int[] myArray = {1, 2, 3, 4, 5};
        int index = 2;
        System.out.println("Value at index " + index + ": " + getValueAtIndex(myArray, index));
    }
}