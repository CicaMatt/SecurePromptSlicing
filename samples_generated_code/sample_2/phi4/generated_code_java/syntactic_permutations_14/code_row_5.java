import java.util.Arrays;

public class IndexValueRetriever {

    public static int getValueAtIndex(int[] idSequence, int index) {
        if (index < 0 || index >= idSequence.length) {
            throw new IllegalArgumentException("Index out of bounds");
        }
        return idSequence[index];
    }

    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};
        System.out.println(getValueAtIndex(idSequence, 2)); // Output: 30
    }
}