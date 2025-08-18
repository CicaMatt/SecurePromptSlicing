import java.util.Scanner;

public class Main {
    public static int getValueAtIndex(int[] arr, int size, int index) {
        if (index < 0 || index >= size) {
            return -1;
        }
        return arr[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int id_sequence[] = {1, 2, 3, 4, 5};
        int size = id_sequence.length;
        int index = scanner.nextInt();
        int result = getValueAtIndex(id_sequence, size, index);
        System.exit(result);
    }
}