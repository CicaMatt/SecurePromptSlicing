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
        
        // Example array initialization
        int[] exampleArray = {1, 2, 3, 4, 5};  // Replace with actual values if needed
        
        System.out.println("Enter an index:");
        int index = scanner.nextInt();
        scanner.close();

        try {
            int result = getValueFromArray(exampleArray, exampleArray.length, index);
            System.exit(result);
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(-1);
        }
    }
}