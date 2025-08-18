import java.util.Arrays;

public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1) return;
        
        String input = args[0];
        char[] chars = input.toCharArray();
        int len = chars.length;
        int lastNonSpace = -1;
        int lastNonNewline = -1;

        for (int i = len - 1; i >= 0; i--) {
            if (!Character.isWhitespace(chars[i])) {
                lastNonSpace = i;
                break;
            }
        }

        for (int i = lastNonSpace; i >= 0; i--) {
            if (chars[i] != '\n' && chars[i] != '\r') {
                lastNonNewline = i;
                break;
            }
        }

        String trimmed = new String(chars, 0, lastNonNewline + 1) + "\0";
        System.out.println(trimmed);
    }
}