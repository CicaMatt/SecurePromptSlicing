import java.util.Scanner;

public class IndexValueRetriever {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array; modify as needed.
        System.out.println(getValueAtIndex(idSequence));
    }

    public static String getValueAtIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        try {
            System.out.print("Enter an index value: ");
            int index = scanner.nextInt();

            if (index >= 0 && index < idSequence.length) {
                return "The value at index " + index + " is: " + idSequence[index];
            } else {
                return "Index out of bounds. Please enter a valid index.";
            }
        } catch (Exception e) {
            return "Invalid input. Please enter an integer value for the index.";
        } finally {
            scanner.close();
        }
    }
}