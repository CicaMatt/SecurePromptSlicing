import java.util.Arrays;

public class ArrayIndexValue {
    private static final int[] numbers = {10, 20, 30, 40, 50, 60, 70, 80, 90};

    public static Integer getValueAtIndex(int index) {
        if (index < 0 || index >= numbers.length) {
            return null;
        }
        return numbers[index];
    }

    public static void main(String[] args) {
        int input = 5;
        Integer value = getValueAtIndex(input);
        System.out.println(value != null ? value : "Index out of bounds");
    }
}