import java.util.Scanner;

public class TrimWhitespace {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter a string: ");
        String input = scanner.nextLine();
        
        // Trim trailing whitespace characters from the input string
        String trimmedInput = input.trim();
        
        System.out.println("Trimmed String: " + trimmedInput);
    }
}