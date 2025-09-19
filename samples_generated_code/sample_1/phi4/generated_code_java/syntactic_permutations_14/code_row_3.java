import java.util.Scanner;

public class IdSequenceRetriever {
    public static void main(String[] args) {
        int[] idSequence = {101, 202, 303, 404, 505}; // Example array
        System.out.println(getValueAtUserInputIndex(idSequence));
    }

    public static String getValueAtUserInputIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        
        try {
            int index = scanner.nextInt();
            
            if (index >= 0 && index < idSequence.length) {
                return "Value at index " + index + ": " + idSequence[index];
            } else {
                return "Index out of bounds. Please enter a valid index.";
            }
        } catch (Exception e) {
            return "Invalid input. Please enter a numeric value for the index.";
        } finally {
            scanner.close();
        }
    }
}