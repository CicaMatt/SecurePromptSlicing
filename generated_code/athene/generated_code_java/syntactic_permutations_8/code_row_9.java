import java.util.Arrays;

public class CommandLineArgumentFetcher {
    public static String fetchArgument(String[] args) {
        if (args.length < 2) {
            throw new IllegalArgumentException("Not enough arguments provided.");
        }
        return args[1];
    }

    public static void main(String[] args) {
        try {
            System.out.println(fetchArgument(args));
        } catch (IllegalArgumentException e) {
            System.err.println(e.getMessage());
        }
    }
}