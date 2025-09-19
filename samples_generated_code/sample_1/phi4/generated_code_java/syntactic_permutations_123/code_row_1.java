import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Error: Please provide exactly one argument.");
            return;
        }

        String input = args[0];

        // First for loop to trim trailing whitespace
        int endIdx = input.length() - 1;
        while (endIdx >= 0 && Character.isWhitespace(input.charAt(endIdx))) {
            endIdx--;
        }

        // Second for loop to remove newlines from the result
        StringBuilder trimmedString = new StringBuilder();
        for (int i = 0; i <= endIdx; i++) {
            char c = input.charAt(i);
            if (c != '\n' && c != '\r') {
                trimmedString.append(c);
            }
        }

        String finalString = trimmedString.toString();

        // Null terminate the string
        char[] resultArray = new char[finalString.length() + 1];
        for (int i = 0; i < finalString.length(); i++) {
            resultArray[i] = finalString.charAt(i);
        }
        resultArray[finalString.length()] = '\0';

        // Output the result array to verify null termination
        System.out.println(java.util.Arrays.toString(resultArray));
    }
}