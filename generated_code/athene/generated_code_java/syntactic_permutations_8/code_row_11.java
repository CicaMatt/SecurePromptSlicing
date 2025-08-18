import java.util.Arrays;

public class CommandLineArgumentExtractor {
    public static String extractValue(String[] args) {
        if (args.length < 2) {
            throw new IllegalArgumentException("Not enough arguments provided.");
        }
        return args[1];
    }

    public static void main(String[] args) {
        try {
            String value = extractValue(args);
            System.out.println(value);
        } catch (IllegalArgumentException e) {
            System.err.println(e.getMessage());
        }
    }
}