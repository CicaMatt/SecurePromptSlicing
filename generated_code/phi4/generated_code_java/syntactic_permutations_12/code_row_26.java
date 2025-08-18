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
        
        System.out.print("Enter an integer: ");
        int inputValue = scanner.nextInt();
        
        int[] exampleArray = {1, 2, 3, 4, 5}; // Example array
        int sizeOfArray = exampleArray.length;
        
        try {
            int resultValue = getValueFromArray(exampleArray, sizeOfArray, inputValue);
            System.exit(resultValue);
        } catch (IllegalArgumentException e) {
            System.err.println(e.getMessage());
            System.exit(1);
        }
    }
}