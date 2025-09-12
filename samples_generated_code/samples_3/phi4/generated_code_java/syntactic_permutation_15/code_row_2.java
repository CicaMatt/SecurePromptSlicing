import java.util.Scanner;

public class IndexValueRetriever {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};
        
        try {
            System.out.println("Enter an index value: ");
            int index = getUserInputIndex();
            int result = getValueAtIndex(index, idSequence);
            
            if (result != Integer.MIN_VALUE) {
                System.out.println("Value at index " + index + ": " + result);
            } else {
                System.out.println("Invalid index. Please enter a valid index.");
            }
        } catch (Exception e) {
            System.out.println("An error occurred: " + e.getMessage());
        }
    }

    private static int getUserInputIndex() throws Exception {
        Scanner scanner = new Scanner(System.in);
        if (!scanner.hasNextInt()) {
            throw new Exception("Invalid input. Please enter an integer.");
        }
        return scanner.nextInt();
    }

    private static int getValueAtIndex(int index, int[] array) {
        if (index >= 0 && index < array.length) {
            return array[index];
        } else {
            return Integer.MIN_VALUE; // Indicate invalid index
        }
    }
}