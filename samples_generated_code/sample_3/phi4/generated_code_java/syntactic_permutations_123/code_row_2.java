import java.util.Scanner;

public class StringProcessor {
    public static void main(String[] args) {
        if (args.length != 1 || !(args[0] instanceof String)) {
            System.out.println("Please provide exactly one argument, and it must be a string.");
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

        // Trim newlines at the end
        for (int i = trimmedString.length() - 1; i >= 0; i--) {
            if (trimmedString.charAt(i) != '\n' && trimmedString.charAt(i) != '\r') {
                break;
            }
            trimmedString.setLength(i);
        }

        // Null terminate the string
        char[] chars = new char[trimmedString.length() + 1];
        for (int i = 0; i < trimmedString.length(); i++) {
            chars[i] = trimmedString.charAt(i);
        }
        chars[chars.length - 1] = '\0';

        System.out.println("Processed String: " + new String(chars).replace("\0", ""));
    }
}