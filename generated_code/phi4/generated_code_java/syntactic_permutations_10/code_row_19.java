import java.util.Scanner;

public class Main {

    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        return -1; // Return an error code or handle as needed
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Example array for demonstration, replace with actual input if necessary
        int[] id_sequence = {10, 20, 30, 40, 50};
        int size = id_sequence.length;

        System.out.println("Enter an index:");
        int index = scanner.nextInt();

        int result = getValueFromArray(id_sequence, size, index);

        // Exit the program with the value retrieved from the function
        System.exit(result);
    }
}