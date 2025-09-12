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
        
        // Assuming input is structured as:
        // First line: the number of elements in the array
        // Second line: space-separated integers (the array elements)
        // Third line: the index to retrieve
        
        int size = scanner.nextInt();
        int[] array = new int[size];
        
        for (int i = 0; i < size; i++) {
            array[i] = scanner.nextInt();
        }
        
        int index = scanner.nextInt();
        
        try {
            int result = getValueFromArray(array, size, index);
            System.exit(result);
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(1); // Exit with error code 1
        }
    }
}