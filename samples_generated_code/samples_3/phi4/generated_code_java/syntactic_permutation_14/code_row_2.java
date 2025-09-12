import java.util.Scanner;

public class IndexValueRetriever {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array
        System.out.println(getValueAtUserProvidedIndex(idSequence));
    }

    public static int getValueAtUserProvidedIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an index value: ");
        int index;
        try {
            index = Integer.parseInt(scanner.nextLine());
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
            return -1; // Indicating error
        }

        if (index >= 0 && index < idSequence.length) {
            return idSequence[index];
        } else {
            System.out.println("Index out of bounds.");
            return -1; // Indicating error
        }
    }
}