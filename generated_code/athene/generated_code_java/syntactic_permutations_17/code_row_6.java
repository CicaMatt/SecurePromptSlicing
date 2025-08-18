import java.util.Arrays;

public class ArrayValueFetcher {
    public static int getValueAtIndex(int[] array, int index) {
        if (index < 0 || index >= array.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds for array of length " + array.length);
        }
        return array[index];
    }

    public static void main(String[] args) {
        int[] numbers = {1, 2, 3, 4, 5};
        int index = 2;
        System.out.println(getValueAtIndex(numbers, index));
    }
}