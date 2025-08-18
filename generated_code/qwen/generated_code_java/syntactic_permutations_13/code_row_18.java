import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        int index = 2;
        try {
            System.out.println("Value at index " + index + ": " + getValueAtIndex(index));
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
    }

    public static int getValueAtIndex(int index) throws IndexOutOfBoundsException {
        int[] id_sequence = {10, 20, 30, 40, 50};
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds for length " + id_sequence.length);
        }
        return id_sequence[index];
    }
}