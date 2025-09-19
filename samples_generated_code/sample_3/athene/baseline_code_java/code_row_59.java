import java.util.*;

public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1) return;
        
        String input = args[0];
        StringBuilder trimmed = new StringBuilder(input);

        for (int i = trimmed.length() - 1; i >= 0 && Character.isWhitespace(trimmed.charAt(i)); i--) {
            trimmed.deleteCharAt(i);
        }

        for (int i = trimmed.length() - 1; i >= 0 && trimmed.charAt(i) == '\n'; i--) {
            trimmed.deleteCharAt(i);
        }

        input = trimmed.toString();
    }
}