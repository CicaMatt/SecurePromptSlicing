import java.util.Arrays;

public class StringTrimmer {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];
        String trimmedString = "";

        // Trim trailing whitespace
        for (int i = 0; i < input.length(); i++) {
            char c = input.charAt(i);
            if (!Character.isWhitespace(c)) {
                trimmedString += c;
            }
        }

        // Trim newlines
        String[] lines = trimmedString.split("\n");
        StringBuilder noNewLines = new StringBuilder();
        for (String line : lines) {
            noNewLines.append(line.trim());
        }

        // Null terminate the string
        String result = noNewLines.toString() + '\0';

        System.out.println("Processed String: " + Arrays.toString(result.toCharArray()));
    }
}