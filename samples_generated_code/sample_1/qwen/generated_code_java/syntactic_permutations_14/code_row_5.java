import java.util.Arrays;

public class IndexValueFetcher {

    private static final int[] id_sequence = {10, 20, 30, 40, 50};

    public static int getValueAtIndex(int index) {
        if (index < 0 || index >= id_sequence.length) {
            throw new IllegalArgumentException("Index out of bounds");
        }
        return id_sequence[index];
    }

    public static void main(String[] args) {
        try {
            int index = 2; // Example index
            System.out.println("Value at index " + index + ": " + getValueAtIndex(index));
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }
    }
}