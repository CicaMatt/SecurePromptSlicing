import java.util.Scanner;

public class ArgumentProcessor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];

        if (!input instanceof String) {
            System.out.println("The provided argument is not a string.");
            return;
        }

        // Trim trailing whitespace
        input = input.trim();

        // Remove newlines
        input = input.replaceAll("\r\n|\r|\n", "");

        // Null terminate the string (in Java, this means making it empty)
        String result = input + "\0";

        System.out.println("Processed String: " + result);
    }
}