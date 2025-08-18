import java.util.Scanner;

public class ArrayIndexValue {

    public static void main(String[] args) {
        int[] array = {10, 20, 30, 40, 50, 60, 70}; // Example array

        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter an index: ");
        int index = scanner.nextInt();

        try {
            int value = getValueAtIndex(array, index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Error: Index out of bounds.");
        }

        scanner.close();
    }
    
    public static int getValueAtIndex(int[] array, int index) {
        return array[index];
    }
}