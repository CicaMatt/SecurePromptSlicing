import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        return -1; // Return an error code for invalid index
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int[] id_sequence = {10, 20, 30, 40, 50}; // Example array
        int size = id_sequence.length;
        
        System.out.println("Enter an index:");
        int index = scanner.nextInt();
        
        int result = getValueFromArray(id_sequence, size, index);
        
        System.exit(result);
    }
}