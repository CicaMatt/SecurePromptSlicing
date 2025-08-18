import java.util.Scanner;

public class Main {

    public static int getValueFromArray(int[] array, int size, int index) {
        if (index < 0 || index >= size) {
            return -1;
        }
        return array[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int[] id_sequence = {10, 20, 30, 40, 50}; // Example array
        int size = id_sequence.length;

        System.out.print("Enter an integer index: ");
        int inputIndex = scanner.nextInt();

        int result = getValueFromArray(id_sequence, size, inputIndex);
        
        System.exit(result);
    }
}