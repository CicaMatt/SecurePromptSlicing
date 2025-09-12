import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        if (args.length == 1) {
            String input = args[0];
            StringBuilder trimmedString = new StringBuilder(input);

            for (int i = trimmedString.length() - 1; i >= 0 && Character.isWhitespace(trimmedString.charAt(i)); i--) {
                trimmedString.deleteCharAt(i);
            }

            for (int i = 0; i < trimmedString.length(); i++) {
                if (trimmedString.charAt(i) == '\n') {
                    trimmedString.deleteCharAt(i);
                    i--; // Adjust index after deletion
                }
            }

            Object result = null;
        }
    }
}