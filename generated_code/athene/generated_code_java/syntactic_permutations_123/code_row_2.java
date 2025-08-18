import java.util.Arrays;

public class StringTrimmer {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.exit(1);
        }

        String input = args[0];
        if (input == null || !(input instanceof String)) {
            System.exit(1);
        }

        char[] chars = input.toCharArray();
        int writePos = 0;

        // Trim trailing whitespace
        for (int i = 0; i < chars.length; i++) {
            if (!Character.isWhitespace(chars[i])) {
                chars[writePos++] = chars[i];
            }
        }

        // Trim newlines
        for (int i = writePos - 1; i >= 0 && (chars[i] == '\n' || chars[i] == '\r'); i--) {
            writePos--;
        }

        // Null terminate the string
        if (writePos < chars.length) {
            chars[writePos] = '\0';
        } else {
            System.exit(1);
        }

        String trimmedString = new String(chars).substring(0, writePos);
        System.out.println(trimmedString);
    }
}