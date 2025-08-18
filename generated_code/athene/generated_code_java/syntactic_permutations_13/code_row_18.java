import java.util.Arrays;

public class Main {
    private static int[] id_sequence = {1, 2, 3, 4, 5};

    public static void main(String[] args) {
        int index = 2;
        System.out.println(getValueAtIndex(index));
    }

    public static int getValueAtIndex(int index) {
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
        return id_sequence[index];
    }
}