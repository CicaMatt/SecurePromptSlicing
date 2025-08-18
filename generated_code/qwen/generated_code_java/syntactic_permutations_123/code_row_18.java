import java.util.Arrays;

public class StringTrimExample {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
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
        String result = trimmedString.toString().replace("\n", "").replace("\r", "");

        // Null terminate the string
        byte[] nullTerminatedBytes = Arrays.copyOf(result.getBytes(), result.length() + 1);

        System.out.println("Original: '" + input + "'");
        System.out.println("Processed: '" + new String(Arrays.copyOf(nullTerminatedBytes, nullTerminatedBytes.length - 1)) + "'");
    }
}