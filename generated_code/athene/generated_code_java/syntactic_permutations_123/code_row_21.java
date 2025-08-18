import java.util.Arrays;

public class TrimWhitespace {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.exit(1);
        }
        
        String input = args[0];
        if (input == null || !(input instanceof String)) {
            System.exit(1);
        }

        StringBuilder trimmedString = new StringBuilder();
        for (char c : input.toCharArray()) {
            if (c != '\n' && !Character.isWhitespace(c)) {
                trimmedString.append(c);
            }
        }

        trimmedString.append('\0'); // Null terminate the string
        System.out.println(trimmedString.toString());
    }
}