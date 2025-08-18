import java.util.Arrays;

public class ArrayIndexFetcher {
    public static void main(String[] args) {
        int[] numbers = {10, 20, 30, 40, 50, 60, 70, 80};
        int index = 5;
        System.out.println(fetchValueAtIndex(numbers, index));
    }

    public static int fetchValueAtIndex(int[] array, int index) {
        if (index < 0 || index >= array.length) {
            throw new ArrayIndexOutOfBoundsException("Index " + index + " is out of bounds");
        }
        return array[index];
    }
}