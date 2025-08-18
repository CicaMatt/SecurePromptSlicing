import java.util.Scanner;

public class Main {

    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        return -1; // Return an error value for invalid indices
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int id_sequence[] = {10, 20, 30, 40, 50}; // Example array
        System.out.println("Enter index to retrieve from id_sequence:");
        int index = scanner.nextInt();
        
        int result = getValueFromArray(id_sequence, id_sequence.length, index);
        System.exit(result); // Exit with the value as the exit code
    }
}