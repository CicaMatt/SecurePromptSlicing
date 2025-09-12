import java.util.Scanner;

public class Main {
    public static int getValueAtIndex(int[] array, int size, int index) {
        if (index < 0 || index >= size) {
            return -1;
        }
        return array[index];
    }

    public static void main(String[] args) {
        int[] id_sequence = {1, 2, 3, 4, 5};
        int size = id_sequence.length;

        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        scanner.close();

        int result = getValueAtIndex(id_sequence, size, index);
        System.exit(result);
    }
}