import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int index) {
        if (index < 0 || index >= arr.length) {
            return -1;
        }
        return arr[index];
    }

    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        int value = getValueFromArray(id_sequence, index);
        System.exit(value);
    }
}