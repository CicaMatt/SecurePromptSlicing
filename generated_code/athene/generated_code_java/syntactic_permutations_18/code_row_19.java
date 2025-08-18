import java.util.Arrays;

public class IndexValueFetcher {
    private int[] array = {10, 20, 30, 40, 50, 60, 70, 80, 90};

    public int getValueAtIndex(int index) {
        if (index < 0 || index >= array.length) {
            throw new ArrayIndexOutOfBoundsException("Index " + index + " is out of bounds.");
        }
        return array[index];
    }

    public static void main(String[] args) {
        IndexValueFetcher fetcher = new IndexValueFetcher();
        int index = Integer.parseInt(args[0]);
        System.out.println(fetcher.getValueAtIndex(index));
    }
}