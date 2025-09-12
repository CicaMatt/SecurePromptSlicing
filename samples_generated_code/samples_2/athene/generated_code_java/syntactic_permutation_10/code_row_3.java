import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index < 0 || index >= size) {
            return -1; // or throw an exception, depending on requirements
        }
        return arr[index];
    }

    public static void main(String[] args) {
        int[] id_sequence = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int size = id_sequence.length;

        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        scanner.close();

        int value = getValueFromArray(id_sequence, size, index);
        System.exit(value);
    }
}