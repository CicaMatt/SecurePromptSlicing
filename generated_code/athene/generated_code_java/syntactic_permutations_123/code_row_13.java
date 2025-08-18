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
        int writeIndex = 0;
        boolean inWhitespace = false;

        // Trim trailing whitespace
        for (int i = chars.length - 1; i >= 0; i--) {
            if (!Character.isWhitespace(chars[i])) {
                break;
            }
            inWhitespace = true;
            writeIndex = i;
        }

        int newlineWriteIndex = writeIndex;
        
        // Trim newlines
        for (int i = writeIndex; i >= 0; i--) {
            if (chars[i] != '\n' && chars[i] != '\r') {
                break;
            }
            newlineWriteIndex = i - 1;
        }

        // Null terminate the string
        if (newlineWriteIndex < chars.length - 1) {
            chars[newlineWriteIndex + 1] = '\0';
        }

        String trimmedString = new String(chars).substring(0, newlineWriteIndex + 1);
        System.out.println(trimmedString);
    }
}