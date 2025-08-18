import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        } else {
            System.exit(1);
            return -1; // This line is unreachable but required to compile
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        int[] array = {0, 1, 2, 3, 4, 5}; // Example array
        int size = array.length;
        int result = getValueFromArray(array, size, index);
        System.exit(result);
    }
}