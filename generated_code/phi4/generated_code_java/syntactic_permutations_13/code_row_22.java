import java.util.Scanner;

public class ArrayIndexFetcher {

    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};
        
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter the index to fetch from the array: ");
        int index = scanner.nextInt();
        
        try {
            int value = getValueAtIndex(idSequence, index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Index out of bounds. Please enter a valid index.");
        }
        
        scanner.close();
    }

    public static int getValueAtIndex(int[] array, int index) {
        return array[index];
    }
}