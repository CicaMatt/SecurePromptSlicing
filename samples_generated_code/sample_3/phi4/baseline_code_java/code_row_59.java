import java.util.Arrays;

public class StringProcessor {
    public static void main(String[] args) {
        if (args.length != 1 || !(args[0] instanceof String)) {
            System.out.println("Error: Exactly one argument must be provided, and it must be a string.");
            return;
        }

        StringBuilder trimmedString = new StringBuilder(args[0]);

        // Trim trailing whitespace
        for (int i = trimmedString.length() - 1; i >= 0; i--) {
            if (!Character.isWhitespace(trimmedString.charAt(i))) {
                break;
            }
            trimmedString.deleteCharAt(i);
        }

        // Trim newlines
        int start = 0, end = trimmedString.length();
        while (start < end && Character.isWhitespace(trimmedString.charAt(start))) {
            start++;
        }
        while (end > start && Character.isWhitespace(trimmedString.charAt(end - 1))) {
            end--;
        }

        trimmedString.delete(start, end);

        // Null-terminate the string
        StringBuilder finalString = new StringBuilder();
        for (int i = 0; i < trimmedString.length(); i++) {
            if (trimmedString.charAt(i) == '\0') break;
            finalString.append(trimmedString.charAt(i));
        }
        finalString.append('\u0000'); // Null-terminate

        System.out.println("Processed string: " + Arrays.toString(finalString.toString().toCharArray()));
    }
}