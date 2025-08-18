import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];
        
        // Trim trailing whitespace
        StringBuilder trimmedString = new StringBuilder();
        for (int i = input.length() - 1; i >= 0; i--) {
            if (!Character.isWhitespace(input.charAt(i))) {
                trimmedString.insert(0, input.substring(i + 1));
                break;
            }
        }

        // Trim newlines
        String noNewlineString = trimmedString.toString().replace("\n", "");
        
        // Null terminate the string (simulated by adding a null character at the end)
        StringBuilder finalString = new StringBuilder(noNewlineString);
        finalString.append('\u0000');

        System.out.println("Processed String: " + Arrays.toString(finalString.toString().toCharArray()));
    }
}