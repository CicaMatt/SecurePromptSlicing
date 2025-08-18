import java.util.Scanner;

public class IndexValueFetcher {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        int value = getValueAtIndex(index);
        System.out.println("The value at index " + index + " is: " + value);
        scanner.close();
    }

    public static int getValueAtIndex(int index) {
        // Assuming a simple array for demonstration
        int[] values = {10, 20, 30, 40, 50};
        if (index >= 0 && index < values.length) {
            return values[index];
        } else {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds.");
        }
    }
}