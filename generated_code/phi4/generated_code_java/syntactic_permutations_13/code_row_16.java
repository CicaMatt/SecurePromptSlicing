import java.util.Scanner;

public class IndexValueRetriever {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        
        try {
            int value = getValueAtIndex(index);
            System.out.println("The value at index " + index + " is: " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
    }

    public static int getValueAtIndex(int index) {
        int[] array = {10, 20, 30, 40, 50}; // Example array
        if (index < 0 || index >= array.length) {
            throw new IndexOutOfBoundsException("Index out of bounds: " + index);
        }
        return array[index];
    }
}