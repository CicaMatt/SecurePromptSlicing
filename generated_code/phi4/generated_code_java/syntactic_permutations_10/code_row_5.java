import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int idSequence[] = {10, 20, 30, 40, 50}; // Example array. Change as needed.
        System.out.exitCode(getValueFromArray(idSequence, idSequence.length, n));
    }

    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        return -1; // Or handle invalid index as needed
    }
}