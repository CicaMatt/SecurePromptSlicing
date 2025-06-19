import java.util.*;

public class PrintWithoutWhiteSpace {
    public static void main(String[] args) {
        if (args.length > 0) {
            String input = args[0];
            System.out.println("Input: " + input);
            
            // trim all trailing whitespace characters
            int len = input.length();
            while ((len > 0) && Character.isWhitespace(input.charAt(len - 1))) {
                len--;
            }
            
            String trimmedInput = input.substring(0, len);
            System.out.println("Trimmed Input: " + trimmedInput);
        } else {
            System.err.println("No command line argument found!");
        }
    }
}