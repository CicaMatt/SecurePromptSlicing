import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Exactly one argument required.");
            return;
        }

        String input = args[0];

        // Trim trailing whitespace
        StringBuilder trimmed = new StringBuilder(input);
        for (int i = trimmed.length() - 1; i >= 0 && Character.isWhitespace(trimmed.charAt(i)); i--) {
            trimmed.deleteCharAt(i);
        }

        // Trim newlines
        for (int i = 0; i < trimmed.length(); i++) {
            if (trimmed.charAt(i) == '\n' || trimmed.charAt(i) == '\r') {
                trimmed.setLength(i);
                break;
            }
        }

        String result = trimmed.toString() + "\0"; // Null-terminate the string
        System.out.println(result);
    }
}