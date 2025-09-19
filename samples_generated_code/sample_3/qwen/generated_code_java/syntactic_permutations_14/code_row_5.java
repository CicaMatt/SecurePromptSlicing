import java.util.Arrays;

public class SequenceFetcher {

    private static final int[] id_sequence = {10, 20, 30, 40, 50};

    public static int getValueAtIndex(int index) {
        if (index < 0 || index >= id_sequence.length) {
            throw new IllegalArgumentException("Index out of bounds");
        }
        return id_sequence[index];
    }

    public static void main(String[] args) {
        try {
            System.out.println(getValueAtIndex(2)); // Example usage
        } catch (IllegalArgumentException e) {
            System.err.println(e.getMessage());
        }
    }
}