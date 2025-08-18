import java.util.Arrays;

public class ArrayIndexFinder {
    public static void main(String[] args) {
        int[] array = {10, 20, 30, 40, 50, 60, 70};
        int index = findIndex(array, 5);
        System.out.println("Value at index " + 5 + ": " + (index >= 0 ? array[index] : "Index out of bounds"));
    }

    public static int findIndex(int[] array, int input) {
        if (input < 0 || input >= array.length) {
            return -1;
        }
        return input;
    }
}