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
        System.out.println("Enter an integer:");
        int input = scanner.nextInt();
        
        // Example usage
        int[] exampleArray = {10, 20, 30, 40, 50};
        int indexToAccess = 2; // You can modify this as needed
        
        try {
            int result = getValueFromArray(exampleArray, exampleArray.length, indexToAccess);
            System.exit(result);
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(1); // Exit with error code
        }
    }
}