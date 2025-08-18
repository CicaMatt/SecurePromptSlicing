import java.util.Scanner;

public class IdSequenceAccess {

    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array

        try {
            System.out.println(getValueAtIndex(idSequence));
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }

    public static int getValueAtIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        
        try {
            System.out.print("Enter the index: ");
            int index = scanner.nextInt();

            if (index < 0 || index >= idSequence.length) {
                throw new IndexOutOfBoundsException("Index out of bounds: " + index);
            }

            return idSequence[index];
        } finally {
            scanner.close();
        }
    }
}