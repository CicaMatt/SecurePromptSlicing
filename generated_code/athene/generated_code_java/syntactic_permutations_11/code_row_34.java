import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        return -1; // Return -1 for invalid index
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] id_sequence = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int size = id_sequence.length;
        int index = scanner.nextInt();
        int value = getValueFromArray(id_sequence, size, index);
        System.out.println(value);
    }
}