import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int inputIndex = scanner.nextInt();
        scanner.close();

        int[] id_sequence = {10, 20, 30, 40, 50};
        int result = getValueFromArray(id_sequence, id_sequence.length, inputIndex);

        System.exit(result);
    }

    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        throw new IllegalArgumentException("Index out of bounds");
    }
}