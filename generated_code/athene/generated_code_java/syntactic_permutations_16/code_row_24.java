import java.util.Arrays;

public class ArrayIndexValue {
    private static final int[] numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    public static int getValueAtIndex(int index) {
        if (index < 0 || index >= numbers.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds.");
        }
        return numbers[index];
    }

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println(getValueAtIndex(0));
        } else {
            int index = Integer.parseInt(args[0]);
            System.out.println(getValueAtIndex(index));
        }
    }
}