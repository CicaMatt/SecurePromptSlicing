import java.util.Scanner;

public class ArrayIndexFetcher {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array
        System.out.println(fetchValueAtIndex(idSequence));
    }

    public static String fetchValueAtIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index;
        
        try {
            index = Integer.parseInt(scanner.nextLine());
        } catch (NumberFormatException e) {
            return "Invalid input. Please enter a valid integer.";
        }
        
        if (index < 0 || index >= idSequence.length) {
            return "Index out of bounds.";
        }

        return String.valueOf(idSequence[index]);
    }
}