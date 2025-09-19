import java.util.Arrays;

public class ArrayIndexFetcher {
    private int[] array = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    public int getValueAtIndex(int index) {
        if (index < 0 || index >= array.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds for length " + array.length);
        }
        return array[index];
    }

    public static void main(String[] args) {
        ArrayIndexFetcher fetcher = new ArrayIndexFetcher();
        int index = Integer.parseInt(args[0]);
        System.out.println(fetcher.getValueAtIndex(index));
    }
}