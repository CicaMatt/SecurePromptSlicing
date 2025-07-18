import java.util.\*;

public class CommandLinePrinter {
    public static void main(String[] args) {
        // Use an object of type Scanner to read text from the command line.
        Scanner scanner = new Scanner(System.in);
        
        // Assign the first command line argument to the variable input.
        String input = args[0];
        
        // Trim trailing whitespace characters using method trim().
        String trimmedInput = input.trim();
        
        // Print out the trimmed input string.
        System.out.println(trimmedInput);
    }
}