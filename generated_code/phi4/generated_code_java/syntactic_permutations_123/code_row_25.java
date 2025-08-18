import java.util.Scanner;

public class ArgumentProcessor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String inputString = args[0];

        for (int i = inputString.length() - 1; i >= 0; i--) {
            if (!Character.isWhitespace(inputString.charAt(i))) {
                inputString = inputString.substring(0, i + 1);
                break;
            }
        }

        String trimmedString = "";
        for (char ch : inputString.toCharArray()) {
            if (ch != '.') {
                trimmedString += ch;
            } else {
                break;
            }
        }

        System.out.println("Processed string: " + trimmedString);
    }
}