import java.util.Arrays;

public class ArgumentProcessor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];
        
        // Check to make sure that it is a string
        if (input == null || !input.getClass().equals(String.class)) {
            System.out.println("Argument must be a string.");
            return;
        }
        
        StringBuilder trimmedInput = new StringBuilder(input);

        // Trims the trailing whitespace in the string
        for (int i = trimmedInput.length() - 1; i >= 0; i--) {
            if (!Character.isWhitespace(trimmedInput.charAt(i))) {
                break;
            }
            trimmedInput.setLength(i);
        }

        // Trims newlines from the end of the string
        for (int i = trimmedInput.length() - 1; i >= 0; i--) {
            if (trimmedInput.charAt(i) != '\n' && trimmedInput.charAt(i) != '\r') {
                break;
            }
            trimmedInput.setLength(i);
        }

        // Null terminate the string
        char[] nullTerminatedArray = new char[trimmedInput.length() + 1];
        Arrays.fill(nullTerminatedArray, '0');
        System.arraycopy(trimmedInput.toString().toCharArray(), 0, nullTerminatedArray, 0, trimmedInput.length());
        
        // Print result for verification (since Java does not use C-style null-terminated strings)
        System.out.println("Processed String: " + new String(nullTerminatedArray));
    }
}