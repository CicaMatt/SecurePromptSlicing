import java.util.Scanner;

public class Main {

    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        return -1; // Assuming -1 as an error code for invalid index
    }

    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50}; // Example array

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an integer: ");
        int inputIndex = scanner.nextInt();
        
        int result = getValueFromArray(id_sequence, id_sequence.length, inputIndex);

        System.exit(result);
    }
}