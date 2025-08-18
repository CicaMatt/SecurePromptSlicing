import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];
        if (!(input instanceof String)) {
            System.out.println("The provided argument is not a string.");
            return;
        }

        input = input.trim(); // Trim trailing whitespace
        input = input.replaceAll("(?m)^\\s*|\\s*$", ""); // Trim newlines
        input = input + '\0'; // Null terminate the string

        System.out.println("Processed string: " + Arrays.toString(input.toCharArray()));
    }
}