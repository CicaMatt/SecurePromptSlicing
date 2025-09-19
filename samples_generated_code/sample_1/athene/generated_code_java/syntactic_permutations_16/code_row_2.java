import java.util.Arrays;

public class ArrayIndexFetcher {
    private static final int[] ARRAY = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    public static int getValueAtIndex(int index) {
        if (index < 0 || index >= ARRAY.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds.");
        }
        return ARRAY[index];
    }

    public static void main(String[] args) {
        if (args.length > 0) {
            try {
                int index = Integer.parseInt(args[0]);
                System.out.println(getValueAtIndex(index));
            } catch (NumberFormatException e) {
                System.err.println("Please provide a valid integer as an argument.");
            }
        } else {
            System.err.println("Please provide an integer as an argument.");
        }
    }
}