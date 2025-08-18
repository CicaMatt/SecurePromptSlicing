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
        int size = 5; // Example size, can be changed as needed
        int[] array = {10, 20, 30, 40, 50}; // Example array, can be changed as needed

        System.out.println("Enter an index:");
        int index = scanner.nextInt();

        int result = getValueFromArray(array, size, index);
        System.exit(result);
    }
}