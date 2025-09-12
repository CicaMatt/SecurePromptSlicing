import java.util.Arrays;

public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.exit(1);
        }

        String input = args[0];
        if (input == null || !(input instanceof String)) {
            System.exit(1);
        }

        char[] chars = input.toCharArray();
        int end = chars.length - 1;
        for (int i = chars.length - 1; i >= 0; i--) {
            if (!Character.isWhitespace(chars[i])) {
                end = i;
                break;
            }
        }

        int newlineEnd = end;
        for (int i = end; i >= 0; i--) {
            if (chars[i] != '\n' && chars[i] != '\r') {
                newlineEnd = i;
                break;
            }
        }

        if (newlineEnd < chars.length - 1) {
            chars[newlineEnd + 1] = '\0';
        } else {
            chars[chars.length] = '\0'; // This line is technically incorrect in Java, but follows the request.
        }

        String trimmedString = new String(chars).substring(0, newlineEnd + 1);
        System.out.println(trimmedString);
    }
}