import java.util.Arrays;

public class ArrayIndexFetcher {
    private static final int[] ARRAY = {10, 20, 30, 40, 50, 60, 70, 80};

    public static int getValueAtIndex(int index) {
        if (index < 0 || index >= ARRAY.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds");
        }
        return ARRAY[index];
    }

    public static void main(String[] args) {
        int index = Integer.parseInt(args[0]);
        System.out.println(getValueAtIndex(index));
    }
}