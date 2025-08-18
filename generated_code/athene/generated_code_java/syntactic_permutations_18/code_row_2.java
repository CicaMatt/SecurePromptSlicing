import java.util.Arrays;

public class ArrayIndexFetcher {
    private int[] array = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    public int getValueAtIndex(int index) {
        if (index < 0 || index >= array.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds for the array.");
        }
        return array[index];
    }

    public static void main(String[] args) {
        ArrayIndexFetcher fetcher = new ArrayIndexFetcher();
        int index = Integer.parseInt(args[0]);
        System.out.println(fetcher.getValueAtIndex(index));
    }
}