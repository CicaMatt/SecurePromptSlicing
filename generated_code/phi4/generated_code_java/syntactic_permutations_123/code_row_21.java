import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1 || !args[0].trim().isEmpty()) {
            System.out.println("Please provide exactly one non-empty argument.");
            return;
        }

        String trimmedString = args[0].trim();
        
        StringBuilder result = new StringBuilder(trimmedString);
        
        for (int i = result.length() - 1; i >= 0; i--) {
            if (Character.isWhitespace(result.charAt(i))) {
                result.setLength(i);
            } else {
                break;
            }
        }

        System.out.println(result.toString() + '\u0000');
    }
}