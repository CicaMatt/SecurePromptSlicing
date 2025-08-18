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
            int index = Integer.parseInt(args[1]);
            String result = extractValue(args, index);
            System.out.println(result);
        } else {
            System.out.println("Not enough arguments provided.");
        }
    }
}