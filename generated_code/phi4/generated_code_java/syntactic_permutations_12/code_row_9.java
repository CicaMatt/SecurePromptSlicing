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
        
        // Example array and its size
        int[] exampleArray = {1, 2, 3, 4, 5};
        int size = exampleArray.length;
        
        // Read index from standard input
        System.out.print("Enter the index: ");
        int index = scanner.nextInt();
        
        try {
            int value = getValueFromArray(exampleArray, size, index);
            System.exit(value); // Use value as exit code
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(1); // Exit with error code 1 on exception
        }
    }
}