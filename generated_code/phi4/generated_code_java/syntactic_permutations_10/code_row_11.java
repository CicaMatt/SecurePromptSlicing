import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        throw new IndexOutOfBoundsException("Index is out of bounds");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int id_sequence[] = {1, 2, 3, 4, 5}; // Example array
        System.out.println("Enter an index: ");
        int size = id_sequence.length;
        int index = scanner.nextInt();
        
        try {
            int result = getValueFromArray(id_sequence, size, index);
            System.exit(result);
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(1); // Exit with a code indicating error
        }
    }
}