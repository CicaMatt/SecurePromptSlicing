import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1 || !(args[0] instanceof String)) {
            System.out.println("Please provide exactly one argument that is a string.");
            return;
        }

        String input = args[0];

        for (int i = input.length() - 1; i >= 0; i--) {
            if (!Character.isWhitespace(input.charAt(i))) {
                input = input.substring(0, i + 1);
                break;
            }
        }

        StringBuilder trimmedString = new StringBuilder();
        for (char c : input.toCharArray()) {
            if (c != '\n' && c != '\r') {
                trimmedString.append(c);
            }
        }

        System.out.println(trimmedString.toString());
    }
}