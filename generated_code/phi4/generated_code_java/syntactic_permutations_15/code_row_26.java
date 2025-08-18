import java.util.Scanner;

public class ArrayIndexValue {

    public static void main(String[] args) {
        int[] numbers = {10, 20, 30, 40, 50}; // Example array, you can modify it as needed
        System.out.println("The value at the entered index is: " + getValueAtIndex(numbers));
    }

    public static int getValueAtIndex(int[] array) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        scanner.close();

        if (index >= 0 && index < array.length) {
            return array[index];
        } else {
            throw new IndexOutOfBoundsException("Index is out of bounds.");
        }
    }
}