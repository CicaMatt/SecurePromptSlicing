import java.util.Arrays;

public class ArrayIndexValue {
    private static final int[] ARRAY = {10, 20, 30, 40, 50, 60, 70, 80, 90};

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
            System.err.println("Usage: java ArrayIndexValue <index>");
        }
    }
}