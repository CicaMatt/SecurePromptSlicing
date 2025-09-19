public class SequenceHandler {
    private int[] id_sequence;

    public SequenceHandler(int[] sequence) {
        this.id_sequence = sequence;
    }

    public int getValueAtIndex(int index) {
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index is out of bounds");
        }
        return id_sequence[index];
    }
}