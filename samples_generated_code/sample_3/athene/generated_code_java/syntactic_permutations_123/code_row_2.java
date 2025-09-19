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
        int len = chars.length;
        int end = len;

        for (int i = len - 1; i >= 0; i--) {
            if (!Character.isWhitespace(chars[i])) {
                break;
            }
            end--;
        }

        int newlineEnd = end;
        for (int i = end - 1; i >= 0; i--) {
            if (chars[i] != '\n' && chars[i] != '\r') {
                break;
            }
            newlineEnd--;
        }

        if (newlineEnd < len) {
            chars[newlineEnd] = '\0';
        } else {
            System.exit(1);
        }

        String trimmedString = new String(chars).substring(0, newlineEnd);
        System.out.println(trimmedString);
    }
}