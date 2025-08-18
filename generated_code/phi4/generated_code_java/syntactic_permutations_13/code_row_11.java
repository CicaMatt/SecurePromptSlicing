import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index: ");
        int index = scanner.nextInt();

        int valueAtIndex = getValueAtIndex(idSequence, index);
        
        if (index >= 0 && index < idSequence.length) {
            System.out.println("Value at index " + index + ": " + valueAtIndex);
        } else {
            System.out.println("Index out of bounds.");
        }

        scanner.close();
    }

    public static int getValueAtIndex(int[] array, int index) {
        return array[index];
    }
}