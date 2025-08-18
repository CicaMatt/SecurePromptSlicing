import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int idx) {
        if (idx >= 0 && idx < size) {
            return arr[idx];
        }
        return -1; // Return -1 if index is out of bounds
    }

    public static void main(String[] args) {
        int[] id_sequence = {1, 2, 3, 4, 5};
        int size = id_sequence.length;
        
        Scanner scanner = new Scanner(System.in);
        int idx = scanner.nextInt();
        scanner.close();

        int result = getValueFromArray(id_sequence, size, idx);
        System.exit(result);
    }
}