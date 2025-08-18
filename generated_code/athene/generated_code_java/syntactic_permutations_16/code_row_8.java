import java.util.Arrays;

public class ArrayIndexFetcher {
    public static int getValueAtIndex(int[] array, int index) {
        if (index < 0 || index >= array.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds for array of length " + array.length);
        }
        return array[index];
    }

    public static void main(String[] args) {
        int[] sampleArray = {10, 20, 30, 40, 50, 60, 70};
        int index = 5;
        System.out.println("Value at index " + index + ": " + getValueAtIndex(sampleArray, index));
    }
}