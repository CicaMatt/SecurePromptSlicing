import java.util.Scanner;

public class ArrayValueFetcher {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        return -1; // Return a default value or handle error as needed
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an integer: ");
        int inputValue = scanner.nextInt();
        
        int[] exampleArray = {10, 20, 30, 40, 50}; // Example array for demonstration
        int size = exampleArray.length;
        int indexToFetch = inputValue; // Assuming the input is used as the index

        int result = getValueFromArray(exampleArray, size, indexToFetch);

        System.exit(result);
    }
}