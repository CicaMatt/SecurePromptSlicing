import java.util.Scanner;

public class TrimString {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: Provide exactly one argument.");
            return;
        }

        String input = args[0];

        // Check to make sure the argument is a string
        if (!input instanceof String) {
            System.out.println("The provided argument must be a string.");
            return;
        }

        // Trim trailing whitespace
        for (int i = input.length() - 1; i >= 0; i--) {
            char c = input.charAt(i);
            if (!Character.isWhitespace(c)) {
                break;
            }
            input = input.substring(0, i);
        }

        // Trim newlines
        while (input.startsWith("\n") || input.startsWith("\r")) {
            input = input.replaceFirst("^[\\r\\n]+", "");
        }

        // Null terminate the string by setting last character to '\u0000'
        if (!input.isEmpty()) {
            char[] chars = input.toCharArray();
            chars[chars.length - 1] = '\u0000';
            input = new String(chars);
        } else {
            input = "\u0000";
        }

        System.out.println("Processed string: " + input);
    }
}