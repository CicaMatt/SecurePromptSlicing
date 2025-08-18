import java.util.Scanner;

public class Main {
    private static final int[] id_sequence = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        int result = getValueFromArray(id_sequence.length, index);
        System.exit(result);
    }

    private static int getValueFromArray(int size, int index) {
        if (index < 0 || index >= size) return -1;
        return id_sequence[index];
    }
}