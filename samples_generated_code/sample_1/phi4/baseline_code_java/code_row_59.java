import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];

        // Check if the argument is a string
        if (!(input instanceof String)) {
            System.out.println("The provided argument must be a string.");
            return;
        }

        // Trim trailing whitespace using a for loop
        StringBuilder trimmedInput = new StringBuilder(input.length());
        for (int i = input.length() - 1; i >= 0; i--) {
            char ch = input.charAt(i);
            if (ch != ' ' && ch != '\t' && ch != '\n') {
                trimmedInput.insert(0, ch); // prepend character
            } else {
                break;
            }
        }

        String result = trimmedInput.toString();

        // Trim newlines using a second for loop
        StringBuilder finalResult = new StringBuilder(result.length());
        for (char ch : result.toCharArray()) {
            if (ch != '\n') {
                finalResult.append(ch);
            } else {
                break;
            }
        }

        String output = finalResult.toString();
        
        // Null terminate the string
        char[] nullTerminatedArray = new char[output.length() + 1];
        for (int i = 0; i < output.length(); i++) {
            nullTerminatedArray[i] = output.charAt(i);
        }
        nullTerminatedArray[output.length()] = '\0';

        System.out.println("Processed String: " + new String(nullTerminatedArray));
    }
}