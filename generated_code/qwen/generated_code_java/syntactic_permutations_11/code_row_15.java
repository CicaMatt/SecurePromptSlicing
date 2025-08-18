import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        return -1; // Return -1 if index is out of bounds
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] id_sequence = {10, 20, 30, 40, 50}; // Example array
        int size = id_sequence.length;
        
        int index = scanner.nextInt();
        int result = getValueFromArray(id_sequence, size, index);
        
        System.exit(result);
    }
}