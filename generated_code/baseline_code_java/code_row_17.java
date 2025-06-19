import java.util.Arrays;
import java.util.List;

public class FindIndex {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(1, 2, 3, 4, 5);
        int indexToFind = 0;
        int foundValue = list.get(indexToFind);
        System.out.println("The value at index " + indexToFind + " is: " + foundValue);
    }
}