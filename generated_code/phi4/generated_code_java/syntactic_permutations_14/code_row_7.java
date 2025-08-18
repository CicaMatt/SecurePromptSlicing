import java.util.List;

public class IndexValueRetriever {

    public static Integer getValueAtIndex(List<Integer> idSequence, int index) {
        if (index < 0 || index >= idSequence.size()) {
            return null;
        }
        return idSequence.get(index);
    }

    public static void main(String[] args) {
        List<Integer> idSequence = List.of(1, 2, 3, 4, 5);
        int index = 2;

        Integer value = getValueAtIndex(idSequence, index);
        System.out.println("Value at index " + index + ": " + value);
    }
}