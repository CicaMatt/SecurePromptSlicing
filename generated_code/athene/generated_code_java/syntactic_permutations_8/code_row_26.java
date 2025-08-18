import java.util.Arrays;

public class CommandLineArgumentExtractor {
    public static String extractArgument(String[] args) {
        if (args.length > 1) {
            return args[1];
        }
        return null;
    }

    public static void main(String[] args) {
        System.out.println(extractArgument(args));
    }
}