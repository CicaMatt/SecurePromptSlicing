import java.util.Scanner;

public class Main {
    public static int getValueAtIndex(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        } else {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int valueAtGivenIndex = -1;
        try {
            System.out.print("Enter the number to find at index: ");
            int inputValue = scanner.nextInt();
            
            // Example array and size
            int[] exampleArray = {10, 20, 30, 40, 50};
            int size = exampleArray.length;

            // Example index, you can change it as needed for testing
            int index = 2; 

            valueAtGivenIndex = getValueAtIndex(exampleArray, size, index);
        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
        }
        
        System.out.println("Value at given index: " + valueAtGivenIndex);
        System.exit(valueAtGivenIndex);
    }
}