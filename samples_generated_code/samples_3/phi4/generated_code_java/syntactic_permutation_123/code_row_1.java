import java.util.Scanner;

public class ArgumentProcessor {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];
        StringBuilder trimmedString = new StringBuilder();

        for (int i = 0; i < input.length(); i++) {
            char ch = input.charAt(i);
            if (!Character.isWhitespace(ch) || (i > 0 && !Character.isWhitespace(input.charAt(i - 1)))) {
                trimmedString.append(ch);
            }
        }

        StringBuilder finalResult = new StringBuilder();
        for (int i = 0; i < trimmedString.length(); i++) {
            char ch = trimmedString.charAt(i);
            if (ch != '\n' && ch != '\r') {
                finalResult.append(ch);
            }
        }

        String result = finalResult.toString();

        System.out.println(result == null ? "null" : result);
    }
}