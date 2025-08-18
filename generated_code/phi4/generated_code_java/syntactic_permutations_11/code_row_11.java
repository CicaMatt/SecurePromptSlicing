import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        return -1; // or some error value indicating out-of-bounds access
    }

    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50}; // Example array

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        
        int result = getValueFromArray(id_sequence, id_sequence.length, index);

        // Exit with the value as exit code
        System.exit(result);
    }
}