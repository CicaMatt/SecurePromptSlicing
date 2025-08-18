import java.util.Arrays;

public class ArrayIndexFetcher {
    private int[] array = {10, 20, 30, 40, 50};

    public int fetchValue(int index) {
        if (index < 0 || index >= array.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds.");
        }
        return array[index];
    }

    public static void main(String[] args) {
        ArrayIndexFetcher fetcher = new ArrayIndexFetcher();
        int index = Integer.parseInt(args[0]);
        System.out.println(fetcher.fetchValue(index));
    }
}