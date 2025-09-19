import java.util.Arrays;

public class SequenceAccess {
    private int[] id_sequence = {1, 2, 3, 4, 5};

    public int getValueAtIndex(int index) {
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds");
        }
        return id_sequence[index];
    }

    public static void main(String[] args) {
        SequenceAccess sa = new SequenceAccess();
        int index = 3;
        System.out.println(sa.getValueAtIndex(index));
    }
}