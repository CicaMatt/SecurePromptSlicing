import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        return -1; // Return -1 for invalid index
    }

    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        int size = id_sequence.length;

        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        scanner.close();

        int value = getValueFromArray(id_sequence, size, index);
        System.exit(value);
    }
}