import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        if (args.length == 1) {
            String input = args[0];
            StringBuilder trimmedString = new StringBuilder();

            // Trim spaces from each character in the string
            for (char c : input.toCharArray()) {
                if (!Character.isWhitespace(c)) {
                    trimmedString.append(c);
                }
            }

            // Remove newline characters
            for (int i = 0; i < trimmedString.length(); i++) {
                if (trimmedString.charAt(i) == '\n' || trimmedString.charAt(i) == '\r') {
                    trimmedString.deleteCharAt(i);
                    i--; // Adjust index after deletion
                }
            }

            // Null terminate the string
            trimmedString.append('\0');

            System.out.println(trimmedString.toString());
        } else {
            System.out.println("Please provide exactly one argument.");
        }
    }
}