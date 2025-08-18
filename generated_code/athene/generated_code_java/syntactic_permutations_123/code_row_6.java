import java.util.Arrays;

public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1) return;
        
        String input = args[0];
        
        int len = input.length();
        while (len > 0 && Character.isWhitespace(input.charAt(len - 1))) {
            len--;
        }
        
        StringBuilder trimmed = new StringBuilder(input.substring(0, len));
        
        len = trimmed.length();
        while (len > 0 && trimmed.charAt(len - 1) == '\n') {
            len--;
        }
        
        String result = trimmed.substring(0, len);
        args[0] = result + "\0";
    }
}