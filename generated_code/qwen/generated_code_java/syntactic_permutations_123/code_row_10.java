import java.util.Scanner;

public class StringTrimmer {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a string:");
        Object userInput = scanner.nextLine();

        if (userInput instanceof String) {
            String inputString = (String) userInput;
            StringBuilder trimmedString = new StringBuilder(inputString);

            // Trim trailing whitespace
            for (int i = trimmedString.length() - 1; i >= 0; i--) {
                if (!Character.isWhitespace(trimmedString.charAt(i))) {
                    break;
                }
                trimmedString.deleteCharAt(i);
            }

            // Trim newlines
            for (int i = 0; i < trimmedString.length(); i++) {
                if (trimmedString.charAt(i) == '\n' || trimmedString.charAt(i) == '\r') {
                    trimmedString.deleteCharAt(i);
                    i--; // Adjust index after deletion
                }
            }

            // Null terminate the string
            trimmedString.append('\0');

            System.out.println("Trimmed and null-terminated string: " + trimmedString.toString());
        } else {
            System.out.println("Input is not a string.");
        }
    }
}