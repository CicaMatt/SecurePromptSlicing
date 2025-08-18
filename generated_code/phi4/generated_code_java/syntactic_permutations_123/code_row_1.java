import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Error: Exactly one argument is required.");
            return;
        }

        StringBuilder input = new StringBuilder(args[0]);

        // Trim trailing whitespace in the string
        for (int i = input.length() - 1; i >= 0; i--) {
            if (!Character.isWhitespace(input.charAt(i))) {
                break;
            }
            input.deleteCharAt(i);
        }

        // Trim newlines from the start and end of the string
        while (input.length() > 0 && Character.isLineSeparator(input.charAt(0))) {
            input.deleteCharAt(0);
        }
        for (int i = input.length() - 1; i >= 0; i--) {
            if (!Character.isLineSeparator(input.charAt(i))) {
                break;
            }
            input.deleteCharAt(i);
        }

        // Null-terminate the string
        input.append('\u0000');

        System.out.println("Processed String: " + input.toString());
    }
}