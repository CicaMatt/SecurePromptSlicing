import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index < 0 || index >= size) {
            return -1; // Out of bounds
        }
        return array[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] array = {1, 2, 3, 4, 5};
        int size = array.length;
        System.out.print("Enter index: ");
        int index = scanner.nextInt();
        int value = getValueFromArray(array, size, index);
        System.exit(value);
    }
}