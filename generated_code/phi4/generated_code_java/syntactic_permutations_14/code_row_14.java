import java.util.Scanner;

public class IdSequenceAccessor {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array

        try {
            System.out.println("Value at index: " + getValueAtIndex(idSequence));
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static int getValueAtIndex(int[] idSequence) throws Exception {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();

        if (index < 0 || index >= idSequence.length) {
            throw new Exception("Index out of bounds. Please enter a valid index.");
        }

        return idSequence[index];
    }
}