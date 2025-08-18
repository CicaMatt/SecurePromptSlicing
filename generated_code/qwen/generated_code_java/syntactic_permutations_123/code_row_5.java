import java.util.Scanner;

public class StringTrimmer {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a string:");
        String input = scanner.nextLine();
        
        // Trim trailing whitespace
        for (int i = input.length() - 1; i >= 0; i--) {
            if (!Character.isWhitespace(input.charAt(i))) {
                input = input.substring(0, i + 1);
                break;
            }
        }

        // Trim newlines
        for (int i = input.length() - 1; i >= 0; i--) {
            if (input.charAt(i) != '\n') {
                input = input.substring(0, i + 1);
                break;
            }
        }

        // Null terminate the string
        input = input + '\0';

        System.out.println("Processed string: " + input);
    }
}