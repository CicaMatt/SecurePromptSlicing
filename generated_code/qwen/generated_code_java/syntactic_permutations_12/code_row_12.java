import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int index) {
        return array[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        int[] array = {10, 20, 30, 40, 50}; // Example array
        int result = getValueFromArray(array, index);
        System.exit(result);
    }
}