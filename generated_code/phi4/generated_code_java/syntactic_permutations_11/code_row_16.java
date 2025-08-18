import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int n = Integer.parseInt(scanner.nextLine());
        int[] id_sequence = new int[n];
        
        for (int i = 0; i < n; i++) {
            id_sequence[i] = scanner.nextInt();
        }
        
        int index = scanner.nextInt();
        System.exit(getValueFromArray(id_sequence, n, index));
    }

    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        } else {
            System.err.println("Index out of bounds");
            System.exit(1);
            return -1; // This line will never be reached
        }
    }
}