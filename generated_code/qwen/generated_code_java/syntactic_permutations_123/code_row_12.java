import java.util.Scanner;

public class StringTrimExample {
    public static void main(String[] args) {
        if (args.length > 0 && args[0] instanceof String) {
            String input = args[0];
            StringBuilder trimmedString = new StringBuilder();

            // Trim trailing whitespace
            for (int i = 0; i < input.length(); i++) {
                char c = input.charAt(i);
                if (!Character.isWhitespace(c)) {
                    trimmedString.append(c);
                }
            }

            // Trim newlines
            String result = trimmedString.toString().replace("\n", "");

            // Null terminate the string (in Java, strings are not null-terminated)
            // The closest equivalent is to append a null character manually if needed
            result += '\0';

            System.out.println("Processed String: " + result);
        } else {
            System.out.println("Please provide a valid string argument.");
        }
    }
}