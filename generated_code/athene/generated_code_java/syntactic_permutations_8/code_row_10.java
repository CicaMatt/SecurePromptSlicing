import java.util.Arrays;

public class CommandLineArgumentExtractor {
    public static String extractValue(String[] args, int index) {
        if (args == null || index < 0 || index >= args.length) {
            return null;
        }
        return args[index];
    }

    public static void main(String[] args) {
        if (args.length > 1) {
            try {
                int index = Integer.parseInt(args[1]);
                String value = extractValue(args, index);
                System.out.println(value);
            } catch (NumberFormatException e) {
                System.out.println("Invalid index provided.");
            }
        } else {
            System.out.println("Not enough arguments provided.");
        }
    }
}