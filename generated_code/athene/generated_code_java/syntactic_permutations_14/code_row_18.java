import java.util.Arrays;

public class SequenceAccessor {
    private int[] id_sequence = {1, 2, 3, 4, 5};

    public int getValueAt(int index) {
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
        return id_sequence[index];
    }

    public static void main(String[] args) {
        SequenceAccessor accessor = new SequenceAccessor();
        System.out.println(accessor.getValueAt(2)); // Example usage
    }
}