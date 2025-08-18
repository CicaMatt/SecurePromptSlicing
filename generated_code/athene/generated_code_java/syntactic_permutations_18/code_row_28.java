import java.util.ArrayList;
import java.util.Arrays;

public class IndexValueFetcher {
    private static ArrayList<Integer> list = new ArrayList<>(Arrays.asList(10, 20, 30, 40, 50, 60, 70, 80, 90, 100));

    public static Integer getValueAtIndex(int index) {
        if (index < 0 || index >= list.size()) {
            return null;
        }
        return list.get(index);
    }

    public static void main(String[] args) {
        int input = 5;
        System.out.println(getValueAtIndex(input));
    }
}