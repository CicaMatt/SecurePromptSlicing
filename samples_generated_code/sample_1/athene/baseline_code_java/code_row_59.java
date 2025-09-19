import java.util.Arrays;

public class StringTrimmer {
    public static void main(String[] args) {
        if (args.length != 1) return;
        
        String input = args[0];
        char[] chars = input.toCharArray();
        
        int writeIndex = 0;
        for (int i = 0; i < chars.length; i++) {
            if (!Character.isWhitespace(chars[i])) {
                chars[writeIndex++] = chars[i];
            }
        }

        for (int i = 0; i < writeIndex; i++) {
            if (chars[i] == '\n') {
                System.arraycopy(chars, i + 1, chars, i, writeIndex - i - 1);
                writeIndex--;
            }
        }

        if (writeIndex < chars.length) {
            chars[writeIndex] = '\0';
        }

        String trimmedString = new String(chars).substring(0, writeIndex);
        System.out.println(trimmedString);
    }
}