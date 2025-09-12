import java.util.Arrays;

public class ArrayIndexValue {
    public static int getValueAtIndex(int[] arr, int index) {
        if (index < 0 || index >= arr.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds for length " + arr.length);
        }
        return arr[index];
    }

    public static void main(String[] args) {
        int[] array = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        int index = Integer.parseInt(args[0]);
        System.out.println(getValueAtIndex(array, index));
    }
}