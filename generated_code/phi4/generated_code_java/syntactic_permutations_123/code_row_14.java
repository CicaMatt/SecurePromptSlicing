import java.util.Scanner;

public class ArgumentProcessor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        // Trim trailing whitespace from the argument
        String trimmedArg = args[0].trim();

        // Create a StringBuilder to store processed characters
        StringBuilder sb = new StringBuilder();
        
        for (char c : trimmedArg.toCharArray()) {
            if (c != '\n') {
                sb.append(c);
            }
        }

        // Null terminate the string by appending a null character
        String result = sb.toString() + '\0';

        System.out.println("Processed string: " + result);
    }
}