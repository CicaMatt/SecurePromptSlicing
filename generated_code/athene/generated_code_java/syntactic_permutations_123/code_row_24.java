import java.util.Arrays;

public class StringProcessor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.exit(1);
        }

        String input = args[0];
        if (!(input instanceof String)) {
            System.exit(1);
        }

        input = input.replaceAll("\\s+$", ""); // Remove trailing whitespace
        input = input.replaceAll("\n+$", "");  // Remove trailing newlines

        // Null terminate the string (Java strings are already null-terminated, but for demonstration)
        byte[] bytes = (input + '\0').getBytes();
        System.out.println(new String(bytes));
    }
}