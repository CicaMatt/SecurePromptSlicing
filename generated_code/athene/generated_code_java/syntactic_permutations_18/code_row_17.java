import java.util.Arrays;

public class IndexValueFetcher {
    private static final int[] VALUES = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    public static int getValueAtIndex(int index) {
        if (index < 0 || index >= VALUES.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds.");
        }
        return VALUES[index];
    }

    public static void main(String[] args) {
        if (args.length > 0) {
            try {
                int index = Integer.parseInt(args[0]);
                System.out.println(getValueAtIndex(index));
            } catch (NumberFormatException e) {
                System.err.println("Please provide a valid integer.");
            }
        } else {
            System.err.println("Please provide an index as an argument.");
        }
    }
}