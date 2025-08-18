import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        
        int[] id_sequence = {10, 20, 30, 40, 50}; // Example array
        int size = id_sequence.length;
        
        System.exit(getValueFromArray(id_sequence, size, index));
    }

    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        } else {
            throw new IllegalArgumentException("Index out of bounds");
        }
    }
}