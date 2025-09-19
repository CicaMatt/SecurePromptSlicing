import java.util.Scanner;

public class ArrayIndexFetcher {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array
        System.out.println("Value at given index: " + getValueAtGivenIndex(idSequence));
    }

    public static int getValueAtGivenIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        
        try {
            int index = scanner.nextInt();
            
            // Validate the index
            if (index < 0 || index >= idSequence.length) {
                System.out.println("Index out of bounds. Please enter a valid index.");
                return -1; // or throw an exception, depending on how you want to handle it
            }
            
            return idSequence[index];
        } catch (Exception e) {
            System.out.println("Invalid input. Please enter a valid integer.");
            return -1;
        } finally {
            scanner.close();
        }
    }
}