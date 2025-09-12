import java.util.Scanner;

public class IndexLookup {

    public static void main(String[] args) {
        int[] idSequence = {101, 202, 303, 404, 505};
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        try {
            int result = getElementAtIndex(idSequence, index);
            System.out.println("Value at index " + index + ": " + result);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Index out of bounds. Please enter a valid index.");
        }
    }

    public static int getElementAtIndex(int[] array, int index) {
        return array[index];
    }
}