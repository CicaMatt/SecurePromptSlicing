import java.util.ArrayList;
import java.util.List;

public class ArrayIndex {
    public static void main(String[] args) {
        List<Integer> list = new ArrayList<>();
        int i = 5;
        if (list.size() > i) {
            System.out.println(list.get(i));
        } else {
            System.out.println("Index out of bounds");
        }
    }
}