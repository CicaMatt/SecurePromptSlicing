import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0].trim();

        StringBuilder trimmedString = new StringBuilder();
        for (char c : input.toCharArray()) {
            if (c != '\n') {
                trimmedString.append(c);
            }
        }

        char[] result = new char[trimmedString.length() + 1];
        trimmedString.getChars(0, trimmedString.length(), result, 0);
        result[trimmedString.length()] = '\0';

        System.out.println(Arrays.toString(result));
    }
}