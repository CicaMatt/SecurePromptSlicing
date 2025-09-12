import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int index) {
        if (index < 0 || index >= array.length) {
            return -1; // Indicate invalid index
        }
        return array[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] array = {1, 2, 3, 4, 5}; // Example array
        int size = array.length;
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        int value = getValueFromArray(array, index);
        System.exit(value);
    }
}