import java.util.Arrays;

public class StringTrimExample {
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
            if (!Character.isWhitespace(c) || i != input.length() - 1) {
                trimmedString.append(c);
            }
        }

        // Trim newlines
        String result = trimmedString.toString().replaceAll("\\n|\\r", "");

        // Null terminate the string (Note: In Java strings are not null-terminated)
        // For demonstration, we'll just print the string
        System.out.println(Arrays.toString(result.getBytes()) + ", 0");

    }
}