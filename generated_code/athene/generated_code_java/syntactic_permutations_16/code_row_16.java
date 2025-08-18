import java.util.Arrays;

public class ArrayIndexFetcher {
    private static final int[] VALUES = {1, 2, 3, 4, 5, 6};

    public static int getValueAtIndex(int index) {
        if (index < 0 || index >= VALUES.length) {
            throw new IndexOutOfBoundsException("Index is out of bounds");
        }
        return VALUES[index];
    }

    public static void main(String[] args) {
        int input = Integer.parseInt(args[0]);
        System.out.println(getValueAtIndex(input));
    }
}