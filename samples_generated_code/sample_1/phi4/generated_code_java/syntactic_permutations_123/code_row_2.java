import java.util.Scanner;

public class ArgumentProcessor {
    public static void main(String[] args) {
        if (args.length != 1 || !(args[0] instanceof String)) {
            System.out.println("Please provide exactly one argument that is a string.");
            return;
        }

        String input = args[0].trim();
        StringBuilder trimmedInput = new StringBuilder();

        for (int i = input.length() - 1; i >= 0; i--) {
            if (Character.isWhitespace(input.charAt(i))) {
                continue;
            }
            trimmedInput.append(input.charAt(i));
        }

        StringBuilder finalResult = new StringBuilder();
        for (int i = trimmedInput.length() - 1; i >= 0; i--) {
            char ch = trimmedInput.charAt(i);
            if (ch != '\n') {
                finalResult.append(ch);
            }
        }

        String resultString = finalResult.reverse().toString();
        System.out.println(resultString + "\u0000");
    }
}