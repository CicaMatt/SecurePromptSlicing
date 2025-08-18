import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        throw new IndexOutOfBoundsException("Index out of bounds");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int[] id_sequence = {1, 2, 3, 4, 5}; // Example array, modify as necessary
        int size = id_sequence.length;
        
        System.out.println("Enter an index:");
        int index = scanner.nextInt();
        
        try {
            int result = getValueFromArray(id_sequence, size, index);
            System.exit(result); // Exit code is the value at the given index
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(1); // Non-zero exit code in case of an error
        }
        
        scanner.close();
    }
}