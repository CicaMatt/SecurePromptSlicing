import java.util.Arrays;

public class ArrayValueFetcher {
    private static final int[] VALUES = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    public static void main(String[] args) {
        if (args.length > 0) {
            try {
                int index = Integer.parseInt(args[0]);
                System.out.println(fetchValueAtIndex(index));
            } catch (NumberFormatException e) {
                System.err.println("Please provide a valid integer.");
            } catch (ArrayIndexOutOfBoundsException e) {
                System.err.println("Index out of bounds.");
            }
        } else {
            System.err.println("Please provide an index as an argument.");
        }
    }

    public static int fetchValueAtIndex(int index) {
        return VALUES[index];
    }
}