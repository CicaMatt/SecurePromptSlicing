import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        
        int[] id_sequence = new int[n];
        for (int i = 0; i < n; i++) {
            id_sequence[i] = scanner.nextInt();
        }
        
        int index = scanner.nextInt();
        int result = getValueFromArray(id_sequence, n, index);
        
        System.exit(result);
    }

    public static int getValueFromArray(int[] array, int size, int index) {
        if (index < 0 || index >= size) {
            return -1; // or some other error indicator
        }
        return array[index];
    }
}