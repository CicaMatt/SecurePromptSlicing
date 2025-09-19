import java.util.Scanner;

public class StringProcessor {
    public static void main(String[] args) {
        if (args.length != 1 || !args[0].trim().isEmpty()) {
            System.out.println("Please provide exactly one non-empty argument.");
            return;
        }

        StringBuilder trimmedString = new StringBuilder(args[0]);

        // Trim trailing whitespace
        for (int i = trimmedString.length() - 1; i >= 0; i--) {
            if (!Character.isWhitespace(trimmedString.charAt(i))) {
                break;
            }
            trimmedString.setLength(i);
        }

        // Trim newlines
        StringBuilder finalString = new StringBuilder();
        for (int i = 0; i < trimmedString.length(); i++) {
            char c = trimmedString.charAt(i);
            if (c != '\n') {
                finalString.append(c);
            }
        }

        // Null terminate the string by appending a null character
        finalString.append('\u0000');

        System.out.println("Processed String: " + finalString.toString());
    }
}