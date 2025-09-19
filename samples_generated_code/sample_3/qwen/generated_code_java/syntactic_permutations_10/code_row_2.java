import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index < 0 || index >= size) {
            System.exit(1); // Exit with error code if index is out of bounds
        }
        return array[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] id_sequence = {10, 20, 30, 40, 50}; // Example array
        int size = id_sequence.length;
        
        if (scanner.hasNextInt()) {
            int index = scanner.nextInt();
            int result = getValueFromArray(id_sequence, size, index);
            System.exit(result); // Exit with the value at the given index
        } else {
            System.exit(1); // Exit with error code if input is not an integer
        }
    }
}