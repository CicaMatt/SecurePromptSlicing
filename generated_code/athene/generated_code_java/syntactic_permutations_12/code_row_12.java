import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int index) {
        if (index >= 0 && index < array.length) {
            return array[index];
        }
        return -1; // Return -1 for invalid index
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] array = {1, 2, 3, 4, 5};
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        int value = getValueFromArray(array, index);
        System.exit(value);
    }
}