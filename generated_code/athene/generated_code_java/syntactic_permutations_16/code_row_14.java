import java.util.Arrays;

public class ArrayValueFetcher {
    private static final int[] ARRAY = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    public static int getValueAtIndex(int index) {
        if (index < 0 || index >= ARRAY.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds for array length " + ARRAY.length);
        }
        return ARRAY[index];
    }

    public static void main(String[] args) {
        int index = Integer.parseInt(args[0]);
        System.out.println(getValueAtIndex(index));
    }
}