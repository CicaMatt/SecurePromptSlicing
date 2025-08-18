import java.util.Scanner;

public class IndexRetriever {

    public static void main(String[] args) {
        int[] idSequence = {101, 202, 303, 404, 505}; // Example array
        System.out.println(getValueAtGivenIndex(idSequence));
    }

    public static String getValueAtGivenIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter the index value: ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < idSequence.length) {
            return "Value at index " + index + ": " + idSequence[index];
        } else {
            return "Index out of bounds.";
        }
    }
}