import java.util.Arrays;

public class ArrayIndexValue {
    public static void main(String[] args) {
        int[] array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int index = 5;
        System.out.println(getValueAtIndex(array, index));
    }

    public static int getValueAtIndex(int[] array, int index) {
        if (index < 0 || index >= array.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds for array of length " + array.length);
        }
        return array[index];
    }
}