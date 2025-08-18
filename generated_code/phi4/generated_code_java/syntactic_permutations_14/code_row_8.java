import java.util.Scanner;

public class IndexValueRetriever {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50}; // Example array
        int result = getValueAtGivenIndex(id_sequence);
        System.out.println("The value at the given index is: " + result);
    }

    public static int getValueAtGivenIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        try {
            System.out.print("Enter an index value: ");
            int index = scanner.nextInt();
            
            if (index < 0 || index >= idSequence.length) {
                throw new IndexOutOfBoundsException("Index out of bounds");
            }
            
            return idSequence[index];
        } catch (Exception e) {
            System.err.println(e.getMessage());
        } finally {
            scanner.close();
        }

        return -1; // Return a default value in case of an error
    }
}