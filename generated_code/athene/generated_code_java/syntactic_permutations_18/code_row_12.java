import java.util.Arrays;

public class ArrayValueFetcher {
    private static final int[] values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("No input provided");
            return;
        }
        int index = Integer.parseInt(args[0]);
        try {
            int result = getValueAtIndex(index);
            System.out.println(result);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Index out of bounds: " + index);
        }
    }

    public static int getValueAtIndex(int index) throws IndexOutOfBoundsException {
        return values[index];
    }
}