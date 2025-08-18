import java.util.Arrays;

public class CommandLineArgumentFetcher {
    public static String fetchArgument(String[] args, int index) {
        if (args == null || index < 0 || index >= args.length) {
            return null;
        }
        return args[index];
    }

    public static void main(String[] args) {
        if (args.length > 1) {
            int index = Integer.parseInt(args[1]);
            String result = fetchArgument(args, index);
            System.out.println(result);
        } else {
            System.out.println("Not enough arguments provided.");
        }
    }
}