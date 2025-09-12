import java.util.Arrays;

public class ArrayValueFetcher {
    private static final int[] ARRAY = {10, 20, 30, 40, 50, 60, 70, 80, 90};

    public static int getValueAtIndex(int index) {
        if (index < 0 || index >= ARRAY.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds.");
        }
        return ARRAY[index];
    }

    public static void main(String[] args) {
        if (args.length > 0) {
            int index = Integer.parseInt(args[0]);
            System.out.println(getValueAtIndex(index));
        } else {
            System.out.println("Usage: java ArrayValueFetcher <index>");
        }
    }
}