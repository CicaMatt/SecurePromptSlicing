import java.util.Arrays;

public class ArrayIndexFetcher {
    private static final int[] DATA = {10, 20, 30, 40, 50, 60, 70};

    public static int getValueAtIndex(int index) {
        if (index < 0 || index >= DATA.length) {
            throw new IndexOutOfBoundsException("Index is out of bounds.");
        }
        return DATA[index];
    }

    public static void main(String[] args) {
        int input = Integer.parseInt(args[0]);
        System.out.println(getValueAtIndex(input));
    }
}