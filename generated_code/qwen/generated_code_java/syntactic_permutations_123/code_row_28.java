import java.util.Arrays;

public class TrimAndNullTerminate {
    public static void main(String[] args) {
        if (args.length != 1) {
            throw new IllegalArgumentException("Exactly one argument is required.");
        }

        String input = args[0];
        StringBuilder trimmedString = new StringBuilder();

        // Trim trailing whitespace
        for (int i = 0; i < input.length(); i++) {
            char c = input.charAt(i);
            if (!Character.isWhitespace(c) || i != input.length() - 1 || !Character.isWhitespace(input.charAt(i + 1))) {
                trimmedString.append(c);
            }
        }

        // Trim newlines
        String result = trimmedString.toString().replaceAll("\\n|\\r", "");

        // Null terminate
        byte[] nullTerminatedBytes = Arrays.copyOf(result.getBytes(), result.length() + 1);

        System.out.println(new String(nullTerminatedBytes, 0, nullTerminatedBytes.length - 1));
    }
}