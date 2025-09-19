import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];
        
        for (int i = input.length() - 1; i >= 0; i--) {
            char c = input.charAt(i);
            if (!Character.isWhitespace(c)) break;
            input = input.substring(0, i);
        }
        
        StringBuilder trimmedInput = new StringBuilder(input);

        for (int i = trimmedInput.length() - 1; i >= 0; i--) {
            char c = trimmedInput.charAt(i);
            if (c != '\n') break;
            trimmedInput.deleteCharAt(i);
        }

        String result = trimmedInput.toString();
        result += "\u0000"; // Null-terminate the string
        System.out.println(result);
    }
}