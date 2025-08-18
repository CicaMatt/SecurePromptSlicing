import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        return -1; // Return -1 if index is out of bounds
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        int[] array = {10, 20, 30, 40, 50}; // Example array
        int size = array.length;
        int result = getValueFromArray(array, size, index);
        System.exit(result);
    }
}