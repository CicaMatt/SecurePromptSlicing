import java.util.Arrays;

public class ArrayIndexValue {
    public static int getValueAtIndex(int[] array, int index) {
        if (index < 0 || index >= array.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds for length " + array.length);
        }
        return array[index];
    }

    public static void main(String[] args) {
        int[] numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        int index = 5;
        System.out.println(getValueAtIndex(numbers, index));
    }
}