import java.util.Arrays;

public class IndexValueRetriever {

    public static int getValueAtIndex(int[] idSequence, int index) {
        if (index < 0 || index >= idSequence.length) {
            throw new IndexOutOfBoundsException("Index out of bounds: " + index);
        }
        return idSequence[index];
    }

    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};
        int index = 2;
        
        try {
            int value = getValueAtIndex(idSequence, index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
        }
    }
}