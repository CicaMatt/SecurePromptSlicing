import java.util.Arrays;

public class StringProcessor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Exactly one argument is required.");
            return;
        }

        String input = args[0];
        StringBuilder trimmedString = new StringBuilder();

        // Trim trailing whitespace
        for (int i = 0; i < input.length(); i++) {
            if (!Character.isWhitespace(input.charAt(i))) {
                trimmedString.append(input.charAt(i));
            } else if (i != input.length() - 1 && !Character.isWhitespace(input.charAt(i + 1))) {
                trimmedString.append(input.charAt(i));
            }
        }

        // Trim newlines
        String result = trimmedString.toString().replace("\n", "").replace("\r", "");

        // Null terminate the string (not necessary in Java, but for demonstration)
        byte[] nullTerminatedBytes = Arrays.copyOf(result.getBytes(), result.length() + 1);

        System.out.println(new String(nullTerminatedBytes));
    }
}