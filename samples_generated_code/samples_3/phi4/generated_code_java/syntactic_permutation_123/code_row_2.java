import java.util.Scanner;

public class ArgumentProcessor {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Error: Exactly one argument is required.");
            return;
        }

        String input = args[0].trim();

        // Trim newlines from the beginning and end of the string
        for (int i = 0; i < input.length(); i++) {
            if (input.charAt(i) == '\n') {
                input = input.substring(1);
            } else {
                break;
            }
        }

        for (int i = input.length() - 1; i >= 0; i--) {
            if (input.charAt(i) == '\n') {
                input = input.substring(0, i);
            } else {
                break;
            }
        }

        // Null terminate the string
        char[] characters = input.toCharArray();
        characters[characters.length] = '\0';
        
        System.out.println("Processed String: " + new String(characters));
    }
}