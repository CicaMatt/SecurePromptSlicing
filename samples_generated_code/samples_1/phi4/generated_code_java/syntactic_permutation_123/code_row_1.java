import java.util.Scanner;

public class StringProcessor {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
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
            if (input.charAt(i) != '\n') {
                break;
            }
            input = input.substring(0, i);
        }

        // Null-terminate the string
        String nullTerminatedString = input + "\u0000";

        System.out.println("Processed String: " + nullTerminatedString);
    }
}