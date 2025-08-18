import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];
        char[] chars = input.toCharArray();

        // Trim trailing whitespace
        int end = chars.length - 1;
        while (end >= 0 && Character.isWhitespace(chars[end])) {
            end--;
        }
        
        // Create a new string with trimmed content
        String trimmedString = new String(chars, 0, end + 1);

        // Terminate the string after trimming
        char[] terminatedChars = trimmedString.toCharArray();
        int terminationIndex = terminatedChars.length;
        for (int i = terminationIndex - 1; i >= 0; i--) {
            if (!Character.isWhitespace(terminatedChars[i])) {
                terminationIndex = i + 1;
                break;
            }
        }

        String finalString = new String(terminatedChars, 0, terminationIndex);

        System.out.println("Processed string: '" + finalString + "'");
    }
}