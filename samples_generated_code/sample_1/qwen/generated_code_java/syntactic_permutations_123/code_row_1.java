import java.util.Arrays;

public class Main {
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

        for (int i = trimmedString.length() - 1; i >= 0 && trimmedString.charAt(i) == '\n'; i--) {
            trimmedString.deleteCharAt(i);
        }

        trimmedString.append('\0');

        System.out.println(Arrays.toString(trimmedString.toString().toCharArray()));
    }
}