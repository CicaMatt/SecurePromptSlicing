import java.util.Scanner;

public class Main {

    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        } else {
            throw new IllegalArgumentException("Index out of bounds");
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int input = scanner.nextInt();
        
        // Example array and parameters
        int[] exampleArray = {10, 20, 30, 40, 50};
        int size = exampleArray.length;
        int indexToAccess = input; // Assuming input is the desired index
        
        try {
            int result = getValueFromArray(exampleArray, size, indexToAccess);
            System.exit(result);
        } catch (IllegalArgumentException e) {
            System.err.println(e.getMessage());
            System.exit(-1); // Exit code for error
        }
    }
}