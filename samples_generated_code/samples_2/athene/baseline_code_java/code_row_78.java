import java.util.Scanner;

public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1) return;
        
        String input = args[0];
        int len = input.length();
        int i, j;

        // Trim trailing whitespace
        for (i = len - 1; i >= 0 && Character.isWhitespace(input.charAt(i)); i--) {}
        input = input.substring(0, i + 1);

        // Trim newlines
        for (j = 0; j < input.length() && input.charAt(j) == '\n'; j++) {}
        input = input.substring(j);

        // Null terminate the string (Java strings are already null-terminated)
        System.out.println(input);
    }
}