import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
        return array[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int[] id_sequence = {1, 2, 3, 4, 5}; // Example array
        int size = id_sequence.length;
        
        System.out.println("Enter an integer index:");
        int index = scanner.nextInt();
        
        try {
            int result = getValueFromArray(id_sequence, size, index);
            System.exit(result);
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(1); // Exit with code 1 on error
        }
    }
}