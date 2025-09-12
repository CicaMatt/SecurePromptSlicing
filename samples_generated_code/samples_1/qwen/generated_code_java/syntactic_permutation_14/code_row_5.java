import java.util.Arrays;

public class SequenceFetcher {
    private static final int[] id_sequence = {10, 20, 30, 40, 50};

    public static int getValueAtIndex(int index) {
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds for length " + id_sequence.length);
        }
        return id_sequence[index];
    }

    public static void main(String[] args) {
        int index = 2; // Example index
        try {
            int value = getValueAtIndex(index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
        }
    }
}