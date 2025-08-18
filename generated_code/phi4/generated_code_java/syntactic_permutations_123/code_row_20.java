import java.util.Scanner;

public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];
        StringBuilder trimmedString = new StringBuilder();

        for (int i = 0; i < input.length(); i++) {
            char currentChar = input.charAt(i);
            if (!Character.isWhitespace(currentChar)) {
                trimmedString.append(currentChar);
            }
        }

        String result = trimmedString.toString();
        StringBuilder finalResult = new StringBuilder();

        for (char c : result.toCharArray()) {
            if (c != '\n') {
                finalResult.append(c);
            }
        }

        System.out.println(finalResult.append('\0').toString());
    }
}