import java.util.Arrays;

public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1) return;
        
        String input = args[0];
        if (input == null) return;
        
        char[] chars = input.toCharArray();
        int writeIndex = 0;
        
        // Trim trailing whitespace
        for (int i = chars.length - 1; i >= 0; i--) {
            if (!Character.isWhitespace(chars[i])) break;
            chars[i] = 0;
        }
        
        // Trim newlines
        for (int i = 0; i < chars.length; i++) {
            if (chars[i] != '\n' && chars[i] != '\r') {
                chars[writeIndex++] = chars[i];
            }
        }
        
        // Null terminate the string
        if (writeIndex < chars.length) {
            chars[writeIndex] = 0;
        } else {
            chars[chars.length - 1] = 0;
        }
        
        String trimmedString = new String(chars).trim();
        System.out.println(trimmedString);
    }
}