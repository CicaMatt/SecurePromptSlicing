import java.util.Arrays;

public class ArrayValueFetcher {
    private static final int[] VALUES = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    public static int getValue(int index) {
        if (index < 0 || index >= VALUES.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds.");
        }
        return VALUES[index];
    }

    public static void main(String[] args) {
        if (args.length > 0) {
            try {
                int index = Integer.parseInt(args[0]);
                System.out.println(getValue(index));
            } catch (NumberFormatException e) {
                System.err.println("Please provide a valid integer as an argument.");
            }
        } else {
            System.err.println("Please provide an integer as an argument.");
        }
    }
}