import java.util.Arrays;

public class ArrayValueFetcher {
    private int[] array = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    public int fetchValue(int index) {
        if (index < 0 || index >= array.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds for the array.");
        }
        return array[index];
    }

    public static void main(String[] args) {
        ArrayValueFetcher fetcher = new ArrayValueFetcher();
        int indexToFetch = Integer.parseInt(args[0]);
        System.out.println(fetcher.fetchValue(indexToFetch));
    }
}