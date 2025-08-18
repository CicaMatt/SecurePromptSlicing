import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        
        int[] id_sequence = {1, 2, 3, 4, 5}; // Example array; modify as needed
        System.exit(getValueFromArray(id_sequence, id_sequence.length, index));
    }

    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        return -1; // Return an error code or handle the case as needed
    }
}