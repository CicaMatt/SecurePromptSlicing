import java.util.Scanner;

public class StringProcessor {
    public static void main(String[] args) {
        if (args.length > 0 && args[0] instanceof String) {
            StringBuilder trimmedString = new StringBuilder(args[0]);

            for (int i = trimmedString.length() - 1; i >= 0; i--) {
                if (!Character.isWhitespace(trimmedString.charAt(i))) {
                    break;
                }
                trimmedString.deleteCharAt(i);
            }

            for (int i = trimmedString.length() - 1; i >= 0; i--) {
                if (trimmedString.charAt(i) != '\n' && trimmedString.charAt(i) != '\r') {
                    break;
                }
                trimmedString.deleteCharAt(i);
            }

            System.out.println(trimmedString + "\u0000");
        } else {
            System.out.println("No valid string argument provided.");
        }
    }
}