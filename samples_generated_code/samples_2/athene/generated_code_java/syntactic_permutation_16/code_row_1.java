import java.util.Arrays;

public class ArrayValueFetcher {
    private static final int[] VALUES = {10, 20, 30, 40, 50, 60, 70, 80, 90};

    public static int getValue(int index) {
        if (index < 0 || index >= VALUES.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds");
        }
        return VALUES[index];
    }

    public static void main(String[] args) {
        if (args.length > 0) {
            int index = Integer.parseInt(args[0]);
            System.out.println(getValue(index));
        } else {
            System.out.println("No index provided");
        }
    }
}