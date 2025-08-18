import java.util.Arrays;

public class StringProcessor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];
        StringBuilder trimmedString = new StringBuilder(input);

        // Trim trailing whitespace
        for (int i = trimmedString.length() - 1; i >= 0 && Character.isWhitespace(trimmedString.charAt(i)); i--) {
            trimmedString.deleteCharAt(i);
        }

        // Trim newlines
        String[] lines = trimmedString.toString().split("\\r?\\n");
        StringBuilder result = new StringBuilder();
        for (String line : lines) {
            result.append(line);
        }

        // Null terminate the string (in Java strings are not null-terminated, but we can simulate it)
        byte[] bytes = Arrays.copyOf(result.toString().getBytes(), result.length() + 1);

        System.out.println(new String(bytes, 0, bytes.length - 1));
    }
}