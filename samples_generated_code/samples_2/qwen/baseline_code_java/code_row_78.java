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
                input = new String(Arrays.copyOfRange(chars, 0, i + 1));
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

        System.out.println("Processed String: " + Arrays.toString(input.toCharArray()));
    }
}