import java.util.Scanner;

public class IndexValueFinder {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example sequence
        System.out.println("Enter an index value: ");
        
        Scanner scanner = new Scanner(System.in);
        try {
            int index = scanner.nextInt();
            if (index >= 0 && index < idSequence.length) {
                System.out.println("Value at the given index is: " + getValueAtIndex(index, idSequence));
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (Exception e) {
            System.out.println("Invalid input. Please enter a valid integer index.");
        } finally {
            scanner.close();
        }
    }

    public static int getValueAtIndex(int index, int[] idSequence) {
        return idSequence[index];
    }
}