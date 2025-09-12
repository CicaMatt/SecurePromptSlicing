import java.util.Scanner;

public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1 || !args[0].getClass().equals(args[0])) {
            System.out.println("Please provide exactly one string argument.");
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

        // Trim newlines from the beginning and end of the string
        String trimmedInput = input.trim();
        
        char[] trimmedCharArray = trimmedInput.toCharArray();
        
        // Null-terminate the string
        for (int j = trimmedCharArray.length; j >= 0; j--) {
            if (j == 0 || !Character.isWhitespace(trimmedCharArray[j - 1])) {
                System.out.println(new String(trimmedCharArray, 0, j));
                return;
            }
        }
    }
}