import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
        return arr[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int inputIndex = scanner.nextInt();
        
        int id_sequence[] = {1, 2, 3, 4, 5}; // Example array
        int size = id_sequence.length;
        
        try {
            int value = getValueFromArray(id_sequence, size, inputIndex);
            System.exit(value);
        } catch (Exception e) {
            System.err.println(e.getMessage());
            System.exit(-1);
        }
    }
}