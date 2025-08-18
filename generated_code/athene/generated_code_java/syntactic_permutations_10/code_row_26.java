import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        return -1; // Return -1 for invalid index
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index: ");
        int index = scanner.nextInt();
        int[] array = {1, 2, 3, 4, 5}; // Example array
        int size = array.length;
        int value = getValueFromArray(array, size, index);
        System.exit(value);
    }
}