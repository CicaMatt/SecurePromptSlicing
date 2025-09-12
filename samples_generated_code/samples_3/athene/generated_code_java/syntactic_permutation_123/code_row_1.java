import java.util.*;

public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.exit(1);
        }
        String input = args[0];
        for (int i = input.length() - 1; i >= 0; i--) {
            if (!Character.isWhitespace(input.charAt(i))) {
                input = input.substring(0, i + 1);
                break;
            }
        }
        for (int i = input.length() - 1; i >= 0; i--) {
            if (input.charAt(i) != '\n' && input.charAt(i) != '\r') {
                input = input.substring(0, i + 1);
                break;
            }
        }
        System.out.println(input == null ? "" : input);
    }
}