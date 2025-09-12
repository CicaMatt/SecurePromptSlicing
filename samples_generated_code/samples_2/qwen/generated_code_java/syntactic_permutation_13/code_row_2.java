import java.util.Scanner;

public class IndexValueFetcher {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        try {
            int value = getValueAtIndex(id_sequence, index);
            System.out.println("The value at index " + index + " is: " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Index out of bounds. Please enter a valid index.");
        }
        
        scanner.close();
    }

    public static int getValueAtIndex(int[] array, int index) throws IndexOutOfBoundsException {
        return array[index];
    }
}