import java.util.Arrays;

public class ArrayIndexValue {
    private static final int[] numbers = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    public static int getValueAtIndex(int index) {
        if (index < 0 || index >= numbers.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds");
        }
        return numbers[index];
    }

    public static void main(String[] args) {
        int index = 5;
        System.out.println(getValueAtIndex(index));
    }
}