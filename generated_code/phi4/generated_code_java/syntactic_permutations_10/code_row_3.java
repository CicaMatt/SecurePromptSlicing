import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int inputIndex = scanner.nextInt();
        scanner.close();

        int[] id_sequence = {1, 2, 3, 4, 5}; // Example array
        int value = getValueFromArray(id_sequence, id_sequence.length, inputIndex);

        System.exit(value);
    }

    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        } else {
            throw new IndexOutOfBoundsException("Index out of bounds: " + index);
        }
    }
}