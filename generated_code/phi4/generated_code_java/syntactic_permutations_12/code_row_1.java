import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        throw new IllegalArgumentException("Index out of bounds");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Read the number of elements in the array
        System.out.println("Enter the number of elements:");
        int size = scanner.nextInt();
        
        // Create and populate the array
        int[] array = new int[size];
        System.out.println("Enter the elements:");
        for (int i = 0; i < size; i++) {
            array[i] = scanner.nextInt();
        }
        
        // Read the index to fetch value from
        System.out.println("Enter the index to retrieve value:");
        int index = scanner.nextInt();
        
        // Get the value using getValueFromArray and print it
        try {
            int value = getValueFromArray(array, size, index);
            System.exit(value); // Use exit code as the retrieved value
        } catch (IllegalArgumentException e) {
            System.err.println(e.getMessage());
            System.exit(1); // Exit with error code if index is out of bounds
        }
    }
}