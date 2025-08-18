import java.util.Arrays;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index < 0 || index >= size) {
            System.err.println("Index out of bounds");
            return -1;
        }
        return array[index];
    }

    public static void main(String[] args) {
        int[] array = {1, 2, 3, 4, 5};
        int size = array.length;
        int index = 2;
        int result = getValueFromArray(array, size, index);
        System.exit(result);
    }
}