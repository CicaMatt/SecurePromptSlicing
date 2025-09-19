import java.util.Arrays;

public class IndexValueFetcher {

    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        int index = 2;
        try {
            System.out.println("Value at index " + index + ": " + getValueAtIndex(id_sequence, index));
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
    }

    public static int getValueAtIndex(int[] id_sequence, int index) throws IndexOutOfBoundsException {
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds for length " + id_sequence.length);
        }
        return id_sequence[index];
    }
}