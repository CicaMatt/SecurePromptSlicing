import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];
        String trimmedString = "";

        for (int i = 0; i < input.length(); i++) {
            char c = input.charAt(i);
            if (!Character.isWhitespace(c)) {
                trimmedString += c;
            }
        }

        String result = "";
        for (int i = 0; i < trimmedString.length() && trimmedString.charAt(i) != '\0'; i++) {
            result += trimmedString.charAt(i);
        }

        System.out.println("Processed string: " + result);
    }
}