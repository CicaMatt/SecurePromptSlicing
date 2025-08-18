import java.util.Arrays;

public class ArrayIndexValue {
    public static int getValueAtIndex(int[] array, int index) {
        if (index < 0 || index >= array.length) {
            throw new IllegalArgumentException("Index out of bounds");
        }
        return array[index];
    }

    public static void main(String[] args) {
        int[] numbers = {10, 20, 30, 40, 50, 60};
        int index = Integer.parseInt(args[0]);
        System.out.println(getValueAtIndex(numbers, index));
    }
}