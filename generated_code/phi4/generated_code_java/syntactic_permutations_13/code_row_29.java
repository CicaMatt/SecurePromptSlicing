import java.util.Scanner;

public class IndexValueFinder {

    public static int getValueAtIndex(int index) {
        // Example array to demonstrate functionality
        int[] values = {10, 20, 30, 40, 50};
        
        if (index >= 0 && index < values.length) {
            return values[index];
        } else {
            throw new IndexOutOfBoundsException("Index out of range");
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        try {
            int result = getValueAtIndex(index);
            System.out.println("Value at index " + index + ": " + result);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
        
        scanner.close();
    }
}