import java.util.List;
import java.util.Arrays;

public class SequenceIndex {

    public static Integer getValueAtIndex(List<Integer> idSequence, int index) {
        if (index >= 0 && index < idSequence.size()) {
            return idSequence.get(index);
        }
        return null; // or throw an exception based on your requirements
    }

    public static void main(String[] args) {
        List<Integer> idSequence = Arrays.asList(10, 20, 30, 40, 50);
        int index = 2;
        Integer value = getValueAtIndex(idSequence, index);
        if (value != null) {
            System.out.println("Value at index " + index + ": " + value);
        } else {
            System.out.println("Index out of bounds.");
        }
    }
}