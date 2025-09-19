import java.util.Arrays;

public class ArrayIndexFetcher {
    public static void main(String[] args) {
        int[] array = {10, 20, 30, 40, 50, 60, 70};
        int index = 5;
        System.out.println(fetchValueAtIndex(array, index));
    }

    public static int fetchValueAtIndex(int[] array, int index) {
        if (index < 0 || index >= array.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds for the array.");
        }
        return array[index];
    }
}