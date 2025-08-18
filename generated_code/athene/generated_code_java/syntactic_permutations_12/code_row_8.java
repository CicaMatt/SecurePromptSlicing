import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int index) {
        if (index < 0 || index >= array.length) {
            return -1;
        }
        return array[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int size = scanner.nextInt();
        int[] array = {1, 2, 3, 4, 5}; // Example array
        if (size != array.length) {
            System.exit(1);
        }
        int index = scanner.nextInt();
        int result = getValueFromArray(array, index);
        System.exit(result);
    }
}