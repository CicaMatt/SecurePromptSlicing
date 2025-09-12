import java.util.Arrays;

public class CommandLineArgumentProcessor {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.err.println("Error: No argument provided.");
            System.exit(1);
        }
        String input = args[0];
        System.out.println("Original Input: " + input);
        input = input.trim();
        System.out.println("Trimmed Input: " + input);
        System.exit(0);
    }
}