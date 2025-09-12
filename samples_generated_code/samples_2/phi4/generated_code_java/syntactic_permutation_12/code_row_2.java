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
        System.out.println("Enter the integer value:");
        int inputValue = scanner.nextInt();
        
        int[] exampleArray = {1, 2, 3, 4, 5}; // Example array
        int size = exampleArray.length;

        try {
            int result = getValueFromArray(exampleArray, size, inputValue);
            System.exit(result);
        } catch (IllegalArgumentException e) {
            System.err.println(e.getMessage());
            System.exit(1);
        }
    }
}