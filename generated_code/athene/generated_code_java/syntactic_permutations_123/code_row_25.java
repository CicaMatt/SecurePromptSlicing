import java.util.Arrays;

public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }
        
        String input = args[0];
        
        // Trim trailing whitespace
        for (int i = input.length() - 1; i >= 0; i--) {
            if (!Character.isWhitespace(input.charAt(i))) {
                input = input.substring(0, i + 1);
                break;
            }
        }
        
        // Trim trailing '.'
        for (int i = input.length() - 1; i >= 0; i--) {
            if (input.charAt(i) != '.') {
                input = input.substring(0, i + 1);
                break;
            }
        }

        System.out.println(input);
    }
}