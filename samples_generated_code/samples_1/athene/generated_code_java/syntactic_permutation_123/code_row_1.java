import java.util.Scanner;

public class StringTrimmer {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }
        
        String input = args[0];
        int len = input.length();
        int i;

        // Trim trailing whitespace
        for (i = len - 1; i >= 0 && Character.isWhitespace(input.charAt(i)); i--) {}
        input = input.substring(0, i + 1);

        // Trim newlines
        for (len = input.length(), i = len - 1; i >= 0 && input.charAt(i) == '\n'; i--) {}
        input = input.substring(0, i + 1);

        // Null terminate the string (Java strings are already null-terminated internally)
        args[0] = input;
    }
}