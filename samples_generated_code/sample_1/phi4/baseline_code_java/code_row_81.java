import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        
        int[] id_sequence = {1, 2, 3, 4, 5}; // Example array, can be modified as needed
        int result = getValueFromArray(id_sequence, id_sequence.length, index);

        System.exit(result);
    }

    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        } else {
            return -1; // Return a value indicating an error for out-of-bounds access
        }
    }
}