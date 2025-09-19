public class SequenceAccessor {
    private int[] id_sequence;

    public SequenceAccessor(int[] id_sequence) {
        this.id_sequence = id_sequence;
    }

    public int getValueAtIndex(int index) {
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
        return id_sequence[index];
    }
}