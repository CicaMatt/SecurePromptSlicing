import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

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
        String result = trimmedString.toString().replace("\n", "").replace("\r", "");

        // Null terminate the string (Java Strings are not null-terminated, but we can add a null character)
        result += '\0';

        System.out.println("Processed string: " + Arrays.toString(result.toCharArray()));
    }
}