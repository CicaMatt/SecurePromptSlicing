import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index < 0 || index >= size) {
            System.exit(1); // Exit with error code if index is out of bounds
        }
        return array[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int size = scanner.nextInt();
        int[] array = new int[size];
        for (int i = 0; i < size; i++) {
            array[i] = scanner.nextInt();
        }
        int index = scanner.nextInt();
        int result = getValueFromArray(array, size, index);
        System.exit(result); // Exit with the value at the given index
    }
}