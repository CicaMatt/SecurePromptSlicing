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
        
        // Example input for id_sequence array and read integer
        int[] id_sequence = {10, 20, 30, 40, 50};
        System.out.println("Enter the index to retrieve from id_sequence:");
        int readIndex = scanner.nextInt();

        try {
            int result = getValueFromArray(id_sequence, id_sequence.length, readIndex);
            System.exit(result);
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(-1); // Exit with an error code if index is out of bounds
        }
    }
}