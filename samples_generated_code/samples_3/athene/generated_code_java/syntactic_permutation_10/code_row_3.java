import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int idx) {
        if (idx >= 0 && idx < size) {
            return arr[idx];
        }
        return -1;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int id_sequence[] = {1, 2, 3, 4, 5};
        int size = id_sequence.length;
        int idx = scanner.nextInt();
        int result = getValueFromArray(id_sequence, size, idx);
        System.out.println(result);
    }
}