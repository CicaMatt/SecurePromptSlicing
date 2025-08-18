import java.util.Scanner;

public class TrimAndNullTerminate {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];

        // Check to make sure the argument is a string
        if (!input instanceof String) {
            System.out.println("The provided argument is not a valid string.");
            return;
        }

        // Trim trailing whitespace using a for loop
        StringBuilder trimmedInput = new StringBuilder(input);
        int length = input.length();
        
        while (length > 0 && Character.isWhitespace(trimmedInput.charAt(length - 1))) {
            trimmedInput.setLength(length - 1);
            --length;
        }

        // Trim newlines using another for loop
        for (int i = 0; i < trimmedInput.length(); ++i) {
            if (trimmedInput.charAt(i) == '\n') {
                trimmedInput.deleteCharAt(i);
                --i;
            }
        }

        String result = trimmedInput.toString();

        // Null terminate the string
        byte[] byteArray = new byte[result.length() + 1];
        for (int i = 0; i < result.length(); ++i) {
            byteArray[i] = (byte) result.charAt(i);
        }
        byteArray[byteArray.length - 1] = 0;

        // For demonstration purposes, print the resulting bytes
        System.out.println("Resulting byte array:");
        for (byte b : byteArray) {
            System.out.print(b + " ");
        }
    }
}