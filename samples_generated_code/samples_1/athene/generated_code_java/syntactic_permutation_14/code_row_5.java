import java.util.Arrays;

public class SequenceFinder {
    private int[] id_sequence;

    public SequenceFinder(int[] sequence) {
        this.id_sequence = Arrays.copyOf(sequence, sequence.length);
    }

    public int getValueAt(int index) {
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds.");
        }
        return id_sequence[index];
    }

    public static void main(String[] args) {
        int[] sequence = {1, 2, 3, 4, 5};
        SequenceFinder finder = new SequenceFinder(sequence);
        System.out.println(finder.getValueAt(2)); // Example usage
    }
}