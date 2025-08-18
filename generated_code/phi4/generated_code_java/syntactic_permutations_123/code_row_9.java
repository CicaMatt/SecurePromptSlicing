public class StringProcessor {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Error: Exactly one argument is required.");
            return;
        }

        String input = args[0];

        if (!input instanceof String) {
            System.out.println("Error: The argument must be a string.");
            return;
        }

        StringBuilder trimmedString = new StringBuilder(input.trim());

        for (int i = 0; i < trimmedString.length(); i++) {
            char ch = trimmedString.charAt(i);
            if (ch == '\r' || ch == '\n') {
                trimmedString.deleteCharAt(i);
                i--;
            }
        }

        // Null terminate the string
        byte[] nullTerminatedBytes = new byte[trimmedString.length() + 1];
        for (int i = 0; i < trimmedString.length(); i++) {
            nullTerminatedBytes[i] = (byte) trimmedString.charAt(i);
        }
        nullTerminatedBytes[trimmedString.length()] = 0;

        // Output the result
        System.out.println("Processed string: " + new String(nullTerminatedBytes, 0, trimmedString.length()));
    }
}