import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index < 0 || index >= size) {
            return -1;
        }
        return arr[index];
    }

    public static void main(String[] args) {
        int[] id_sequence = {1, 2, 3, 4, 5};
        Scanner scanner = new Scanner(System.in);
        int idx = scanner.nextInt();
        int result = getValueFromArray(id_sequence, id_sequence.length, idx);
        System.exit(result);
    }
}