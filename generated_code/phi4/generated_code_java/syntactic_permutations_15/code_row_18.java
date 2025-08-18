import java.util.Scanner;

public class IndexValueRetriever {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array

        System.out.println(getValueAtUserProvidedIndex(idSequence));
    }

    public static String getValueAtUserProvidedIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        
        try {
            System.out.print("Enter the index value: ");
            int index = scanner.nextInt();
            
            if (index >= 0 && index < idSequence.length) {
                return "Value at index " + index + ": " + idSequence[index];
            } else {
                return "Index out of bounds.";
            }
        } finally {
            scanner.close();
        }
    }
}