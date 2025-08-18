import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int index) {
        if (index >= 0 && index < arr.length) {
            return arr[index];
        }
        throw new IndexOutOfBoundsException("Index out of bounds");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int inputIndex = scanner.nextInt();
        
        int[] id_sequence = {1, 2, 3, 4, 5}; // Example array
        
        try {
            System.exit(getValueFromArray(id_sequence, inputIndex));
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(1);
        }
    }
}