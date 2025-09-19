import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        } else {
            System.exit(1); // Exit with error code if index is out of bounds
            return -1; // This line is unreachable but added for completeness
        }
    }

    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        scanner.close();

        int result = getValueFromArray(id_sequence, id_sequence.length, index);
        System.exit(result);
    }
}