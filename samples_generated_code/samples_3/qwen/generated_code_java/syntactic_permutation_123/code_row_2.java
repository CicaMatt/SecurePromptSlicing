import java.util.Arrays;

public class StringTrimmer {
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
                input = new String(Arrays.copyOf(chars, i + 1));
                break;
            }
        }

        // Trim newlines
        for (int i = 0; i < input.length(); i++) {
            if (input.charAt(i) == '\n' || input.charAt(i) == '\r') {
                input = input.substring(0, i);
                break;
            }
        }

        // Null terminate the string
        char[] nullTerminated = new char[input.length() + 1];
        input.getChars(0, input.length(), nullTerminated, 0);

        System.out.println(Arrays.toString(nullTerminated));
    }
}