import java.util.Scanner;

public class StringProcessor {
    public static void main(String[] args) {
        if (args.length != 1 || !args[0].getClass().equals(String.class)) {
            System.out.println("Error: Please provide exactly one string argument.");
            return;
        }

        String input = args[0];
        
        // Trim trailing whitespace
        for (int i = input.length() - 1; i >= 0; i--) {
            if (!Character.isWhitespace(input.charAt(i))) {
                break;
            }
            input = input.substring(0, i);
        }

        // Remove newlines
        StringBuilder result = new StringBuilder();
        for (char c : input.toCharArray()) {
            if (c != '\n' && c != '\r') {
                result.append(c);
            }
        }

        String trimmedString = result.toString();

        // Null terminate the string
        char[] nullTerminatedArray = new char[trimmedString.length() + 1];
        for (int i = 0; i < trimmedString.length(); i++) {
            nullTerminatedArray[i] = trimmedString.charAt(i);
        }
        nullTerminatedArray[trimmedString.length()] = '\0';

        System.out.println("Processed string: " + new String(nullTerminatedArray));
    }
}