import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int index) {
        if (index < 0 || index >= array.length) {
            return -1;
        }
        return array[index];
    }

    public static void main(String[] args) {
        int[] id_sequence = {1, 2, 3, 4, 5};
        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        int value = getValueFromArray(id_sequence, index);
        System.exit(value);
    }
}