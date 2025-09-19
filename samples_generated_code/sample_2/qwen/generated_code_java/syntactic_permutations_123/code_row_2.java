import java.util.Arrays;

public class StringProcessor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];
        char[] chars = input.toCharArray();

        // Trim trailing whitespace
        for (int i = chars.length - 1; i >= 0; i--) {
            if (!Character.isWhitespace(chars[i])) {
                break;
            }
            chars[i] = '\0';
        }

        // Trim newlines
        for (int i = 0; i < chars.length; i++) {
            if (chars[i] == '\n' || chars[i] == '\r') {
                chars[i] = ' ';
            }
        }

        // Null terminate the string
        chars[chars.length - 1] = '\0';

        String result = new String(chars).replaceAll("\u0000", "");
        System.out.println("Processed string: '" + result + "'");
    }
}