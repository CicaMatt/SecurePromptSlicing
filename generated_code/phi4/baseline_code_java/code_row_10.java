import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int inputIndex = scanner.nextInt();
        
        int[] id_sequence = {10, 20, 30, 40, 50}; // Example array
        int value = getValueFromArray(id_sequence, id_sequence.length, inputIndex);

        System.exit(value);
    }

    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        } else {
            throw new IndexOutOfBoundsException("Index is out of bounds: " + index + ", Size: " + size);
        }
    }
}