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
        int[] numbers = {10, 20, 30, 40, 50}; // Example array
        int size = numbers.length;

        System.out.println("Enter the index:");
        int index = scanner.nextInt();

        int result = getValueFromArray(numbers, size, index);

        System.exit(result);
    }
}