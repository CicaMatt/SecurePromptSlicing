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
        
        int[] id_sequence = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // example array
        System.out.println("Enter an index:");
        int size = id_sequence.length;
        int index = scanner.nextInt();
        
        try {
            int value = getValueFromArray(id_sequence, size, index);
            System.exit(value);
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(1);
        }
    }
}