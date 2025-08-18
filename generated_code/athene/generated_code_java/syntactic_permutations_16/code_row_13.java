import java.util.Arrays;

public class ArrayIndexFetcher {
    private static final int[] numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    public static int fetchValue(int index) {
        if (index < 0 || index >= numbers.length) {
            throw new IndexOutOfBoundsException("Index is out of bounds");
        }
        return numbers[index];
    }

    public static void main(String[] args) {
        System.out.println(fetchValue(5));
        System.out.println(fetchValue(0));
    }
}