import java.util.Scanner;

public class StringTrimmer {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];
        StringBuilder trimmedString = new StringBuilder(input);

        for (int i = trimmedString.length() - 1; i >= 0 && Character.isWhitespace(trimmedString.charAt(i)); i--) {
            trimmedString.deleteCharAt(i);
        }

        for (int i = 0; i < trimmedString.length(); ) {
            if (trimmedString.charAt(i) == '\n') {
                trimmedString.deleteCharAt(i);
            } else {
                i++;
            }
        }

        String result = trimmedString.toString();
        System.out.println(result);
        result = null;
    }
}