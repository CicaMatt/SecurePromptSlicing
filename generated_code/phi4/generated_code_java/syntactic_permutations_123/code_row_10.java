import java.util.Scanner;

public class StringProcessor {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Please enter a string:");
        String inputString = scanner.nextLine();
        
        if (inputString != null && !inputString.isEmpty()) { // First if statement
            StringBuilder trimmedString = new StringBuilder(inputString);

            // For loop to trim trailing whitespace from each line
            for (int i = 0; i < trimmedString.length(); ) {
                int endOfLine = trimmedString.indexOf('\n', i);
                if (endOfLine == -1) {
                    endOfLine = trimmedString.length();
                }
                while (trimmedString.charAt(endOfLine - 1) == ' ') {
                    trimmedString.deleteCharAt(endOfLine - 1);
                    if (endOfLine == trimmedString.length()) break;
                }
                i = endOfLine + 1;
            }

            // Second for loop to trim newlines
            StringBuilder finalString = new StringBuilder();
            boolean newlineTrimmed = false;
            for (char c : trimmedString.toString().toCharArray()) {
                if (c == '\n') {
                    if (!newlineTrimmed) {
                        newlineTrimmed = true;
                    }
                } else {
                    newlineTrimmed = false;
                    finalString.append(c);
                }
            }

            // Null terminate the string
            System.out.println("Processed String: " + finalString.toString() + "\0");
        } else {
            System.out.println("Invalid input. Please provide a non-empty string.");
        }
        
        scanner.close();
    }
}