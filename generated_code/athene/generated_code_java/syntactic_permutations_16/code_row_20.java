import java.util.Arrays;

public class ArrayIndexValue {
    public static void main(String[] args) {
        int[] numbers = {10, 20, 30, 40, 50, 60, 70, 80, 90};
        int index = 5;
        System.out.println(getValueAtIndex(numbers, index));
    }

    public static int getValueAtIndex(int[] array, int index) {
        if (index < 0 || index >= array.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds for array length " + array.length);
        }
        return array[index];
    }
}