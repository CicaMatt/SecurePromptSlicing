import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int[] id_sequence = {10, 20, 30, 40, 50}; // example array; modify as needed
        
        System.out.println("Enter an index:");
        int index = scanner.nextInt();
        
        try {
            int result = getValueFromArray(id_sequence, id_sequence.length, index);
            System.exit(result);
        } catch (Exception e) {
            System.err.println(e.getMessage());
            System.exit(1);
        }
    }

    public static int getValueFromArray(int[] array, int size, int index) throws IndexOutOfBoundsException {
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException("Index out of bounds: " + index);
        }
        return array[index];
    }
}