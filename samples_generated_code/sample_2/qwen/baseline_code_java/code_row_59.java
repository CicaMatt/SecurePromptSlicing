import java.util.Scanner;

public class StringTrimExample {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];

        // Trim trailing whitespace
        for (int i = input.length() - 1; i >= 0; i--) {
            if (!Character.isWhitespace(input.charAt(i))) {
                input = input.substring(0, i + 1);
                break;
            }
        }

        // Trim newlines
        for (int i = input.length() - 1; i >= 0; i--) {
            if (input.charAt(i) != '\n') {
                input = input.substring(0, i + 1);
                break;
            }
        }

        // Null terminate the string
        input += '\0';

        System.out.println("Processed string: " + input);
    }
}