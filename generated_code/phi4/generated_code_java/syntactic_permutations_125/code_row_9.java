import java.util.Scanner;

public class TrimAndPrint {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter a string:");
        String input = scanner.nextLine();

        // Trim trailing whitespace characters
        String trimmedInput = input.trim();
        
        // Print the original and trimmed strings
        System.out.println("Original Input: '" + input + "'");
        System.out.println("Trimmed Input: '" + trimmedInput + "'");
    }
}