import java.util.Arrays;

public class StringProcessor {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];

        // Ensure the argument is a string
        if (!(input instanceof String)) {
            System.out.println("The provided argument must be a string.");
            return;
        }

        char[] trimmedChars = input.toCharArray();

        // Trim trailing whitespace
        for (int i = trimmedChars.length - 1; i >= 0; i--) {
            if (!Character.isWhitespace(trimmedChars[i])) {
                break;
            }
            trimmedChars[i] = '\0';
        }

        // Trim newlines
        for (int i = trimmedChars.length - 1; i >= 0; i--) {
            if (trimmedChars[i] == '\n') {
                trimmedChars[i] = '\0';
            } else {
                break;
            }
        }

        // Null terminate the string
        String result = new String(trimmedChars).trim() + "\0";

        System.out.println("Processed String: " + result);
    }
}