import java.util.Scanner;

public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1) return;
        
        String input = args[0];
        int length = input.length();
        StringBuilder trimmed = new StringBuilder(input);

        for (int i = length - 1; i >= 0 && Character.isWhitespace(trimmed.charAt(i)); i--) {
            trimmed.deleteCharAt(i);
        }

        length = trimmed.length();
        for (int i = length - 1; i >= 0 && trimmed.charAt(i) == '\n'; i--) {
            trimmed.deleteCharAt(i);
        }

        input = trimmed.toString() + '\0';
        System.out.println(input);
    }
}