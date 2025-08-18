import java.util.Arrays;

public class ArrayValueFetcher {
    private static final int[] numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    public static int fetchValue(int index) {
        if (index < 0 || index >= numbers.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds.");
        }
        return numbers[index];
    }

    public static void main(String[] args) {
        if (args.length > 0) {
            int index = Integer.parseInt(args[0]);
            System.out.println(fetchValue(index));
        } else {
            System.out.println("Please provide an index as an argument.");
        }
    }
}