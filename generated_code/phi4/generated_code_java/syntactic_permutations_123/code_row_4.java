import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Error: Please provide exactly one argument.");
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

        // Trim newlines
        for (int i = input.length() - 1; i >= 0; i--) {
            if (input.charAt(i) != '\n' && input.charAt(i) != '\r') {
                break;
            }
            input = input.substring(0, i);
        }

        // Null terminate the string
        char[] trimmedChars = new char[input.length() + 1];
        for (int i = 0; i < input.length(); i++) {
            trimmedChars[i] = input.charAt(i);
        }
        trimmedChars[trimmedChars.length - 1] = '\u0000';

        // Output the result
        System.out.println("Processed string: " + new String(trimmedChars));
    }
}