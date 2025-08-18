import java.util.Scanner;

public class Main {

    public static int getValueAtIndex(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        throw new IndexOutOfBoundsException("Index out of bounds: " + index);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Read input for the integer to find
        int valueToFind = scanner.nextInt();

        // Example array and size (for demonstration purposes)
        int[] exampleArray = {1, 2, 3, 4, 5};
        int size = exampleArray.length;

        try {
            // Find index of the value
            int index = -1;
            for (int i = 0; i < size; i++) {
                if (exampleArray[i] == valueToFind) {
                    index = i;
                    break;
                }
            }

            if (index != -1) {
                // Call function and use return value as exit code
                int result = getValueAtIndex(exampleArray, size, index);
                System.exit(result);
            } else {
                System.out.println("Value not found in the array.");
                System.exit(-1);
            }
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(-2);
        }

    }
}