import java.util.Scanner;

public class ArrayHelper {
    public static int getValueFromArray(int[] arr, int index) {
        if (index < 0 || index >= arr.length) {
            throw new IllegalArgumentException("Invalid index: " + index);
        }
        return arr[index];
    }
}