import java.util.Scanner;

public class ArgumentProcessor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0].trim();

        StringBuilder trimmedInput = new StringBuilder();
        for (char c : input.toCharArray()) {
            if (c != '\n') {
                trimmedInput.append(c);
            }
        }

        char[] resultArray = trimmedInput.toString().toCharArray();
        resultArray[resultArray.length] = '\0'; // This line will cause an ArrayIndexOutOfBoundsException because it's out of bounds.
        
        System.out.println("Processed String: " + new String(resultArray));
    }
}