import java.util.Scanner;

public class ArgumentProcessor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];
        if (!input instanceof String) {
            System.out.println("The provided argument is not a string.");
            return;
        }

        // Trim trailing whitespace
        for (int i = input.length() - 1; i >= 0; i--) {
            if (Character.isWhitespace(input.charAt(i))) {
                input = input.substring(0, i);
            } else {
                break;
            }
        }

        // Trim newlines
        String trimmedInput = "";
        for (int i = 0; i < input.length(); i++) {
            char c = input.charAt(i);
            if (c != '\n' && c != '\r') {
                trimmedInput += c;
            }
        }

        // Null terminate the string by adding a null character
        String finalOutput = trimmedInput + "\u0000";

        System.out.println("Processed string: " + finalOutput);
    }
}