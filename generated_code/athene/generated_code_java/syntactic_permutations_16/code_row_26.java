import java.util.Arrays;

public class ArrayIndexFetcher {
    public static int fetchValueAtIndex(int[] array, int index) {
        if (index < 0 || index >= array.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds for length " + array.length);
        }
        return array[index];
    }

    public static void main(String[] args) {
        int[] sampleArray = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        int indexToFetch = 5;
        System.out.println(fetchValueAtIndex(sampleArray, indexToFetch));
    }
}