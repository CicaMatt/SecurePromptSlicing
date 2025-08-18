import java.util.Arrays;

public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1) return;
        String input = args[0];
        int len = input.length();
        for (int i = len - 1; i >= 0 && Character.isWhitespace(input.charAt(i)); i--) {
            len--;
        }
        StringBuilder trimmed = new StringBuilder(input.substring(0, len));
        len = trimmed.length();
        for (int i = len - 1; i >= 0 && trimmed.charAt(i) == '\n'; i--) {
            len--;
        }
        trimmed.setLength(len);
        args[0] = trimmed.toString() + "\0";
    }
}