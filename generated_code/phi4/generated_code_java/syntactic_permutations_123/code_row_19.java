import java.util.Scanner;

public class ArgumentProcessor {

    public static void main(String[] args) {
        if (args.length == 1) {
            String input = args[0].trim(); // Trims trailing whitespace

            String trimmedInput = input.replaceAll("\\r\\n|\\r|\\n", ""); // Removes newlines
            StringBuilder nullTerminatedString = new StringBuilder(trimmedInput);
            nullTerminatedString.append('\u0000'); // Appends null character at the end

            System.out.println("Processed string: " + nullTerminatedString.toString());
        } else {
            System.err.println("Please provide exactly one argument.");
        }
    }
}