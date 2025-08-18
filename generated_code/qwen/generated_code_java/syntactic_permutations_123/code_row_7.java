import java.util.Scanner;

public class StringTrimmer {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a string:");
        String input = scanner.nextLine();

        // Trim trailing whitespace
        if (input != null) {
            input = input.replaceAll("\\s+$", "");
        }

        // Remove all newline characters
        for (int i = 0; i < input.length(); i++) {
            input = input.replace("\n", "").replace("\r", "");
        }

        // Null terminate the string (in Java, strings are not null-terminated)
        // This step is redundant in Java as strings do not store a null terminator
        // However, for demonstration, we can create a character array and add a null char at the end
        char[] nullTerminatedString = new char[input.length() + 1];
        input.getChars(0, input.length(), nullTerminatedString, 0);
        nullTerminatedString[input.length()] = '\0';

        System.out.println("Processed string: " + new String(nullTerminatedString));
    }
}