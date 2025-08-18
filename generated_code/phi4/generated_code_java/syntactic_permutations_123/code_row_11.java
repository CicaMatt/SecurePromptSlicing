import java.util.Scanner;

public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1 || !(args[0] instanceof String)) {
            System.out.println("Please provide a single string argument.");
            return;
        }
        
        StringBuilder trimmed = new StringBuilder(args[0]);
        
        for (int i = trimmed.length() - 1; i >= 0; i--) {
            if (!Character.isWhitespace(trimmed.charAt(i))) {
                break;
            }
            trimmed.deleteCharAt(i);
        }

        for (int i = 0; i < trimmed.length(); i++) {
            char ch = trimmed.charAt(i);
            if (ch == '\n' || ch == '\r') {
                trimmed.deleteCharAt(i);
                i--; // Adjust the index after deletion
            }
        }
        
        System.out.println(trimmed + "\u0000");
    }
}