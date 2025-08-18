import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        throw new IndexOutOfBoundsException("Index out of bounds");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Read the integer value from standard input
        int inputValue = scanner.nextInt();
        
        // Define an example array and size for demonstration purposes.
        // In a real use case, these would be provided or dynamically generated.
        int[] exampleArray = {1, 2, 3, 4, 5};
        int size = exampleArray.length;
        int index = inputValue; // Use the input value as the index
        
        try {
            int result = getValueFromArray(exampleArray, size, index);
            System.exit(result); // Return the value at the given index as exit code
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(-1); // Exit with error code -1 if index is out of bounds
        }
    }
}