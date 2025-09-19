import java.util.Scanner;

public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.exit(1);
        }

        String input = args[0];
        if (input == null || !(input instanceof String)) {
            System.exit(1);
        }

        int len = input.length();
        for (int i = len - 1; i >= 0 && Character.isWhitespace(input.charAt(i)); i--) {
            input = input.substring(0, i);
        }

        len = input.length(); // Update length after trimming whitespace
        for (int i = len - 1; i >= 0 && input.charAt(i) == '\n'; i--) {
            input = input.substring(0, i);
        }

        System.out.println(input + "\0");
    }
}