import java.util.Arrays;

public class StringProcessor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];
        StringBuilder trimmedString = new StringBuilder(input);

        // Trim trailing whitespace
        for (int i = trimmedString.length() - 1; i >= 0 && Character.isWhitespace(trimmedString.charAt(i)); i--) {
            trimmedString.deleteCharAt(i);
        }

        // Trim newlines
        for (int i = trimmedString.length() - 1; i >= 0 && (trimmedString.charAt(i) == '\n' || trimmedString.charAt(i) == '\r'); i--) {
            trimmedString.deleteCharAt(i);
        }

        // Null terminate the string
        trimmedString.append('\0');

        System.out.println("Processed String: " + Arrays.toString(trimmedString.toString().toCharArray()));
    }
}