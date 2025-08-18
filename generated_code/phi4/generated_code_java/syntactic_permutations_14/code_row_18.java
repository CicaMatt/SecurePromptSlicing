import java.util.Arrays;

public class IndexValueRetriever {

    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};
        int index = 2;
        
        try {
            System.out.println("Value at index " + index + ": " + getValueAtIndex(idSequence, index));
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Error: Index out of bounds");
        }
    }

    public static int getValueAtIndex(int[] idSequence, int index) {
        return idSequence[index];
    }
}