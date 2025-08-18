import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int index) {
        return array[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] id_sequence = {10, 20, 30, 40, 50};
        int index = scanner.nextInt();
        int result = getValueFromArray(id_sequence, index);
        System.exit(result);
    }
}