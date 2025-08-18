import java.util.Arrays;

public class ArrayValueFetcher {
    private static final int[] DATA = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    public static int getValue(int index) {
        if (index < 0 || index >= DATA.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds.");
        }
        return DATA[index];
    }

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide an integer as an argument.");
            return;
        }
        try {
            int index = Integer.parseInt(args[0]);
            System.out.println(getValue(index));
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please provide a valid integer.");
        }
    }
}