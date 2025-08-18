import java.util.Arrays;

public class CommandLineArgumentFetcher {
    public static String getArgumentValue(String[] args, int index) {
        if (args == null || index < 0 || index >= args.length) {
            return null;
        }
        return args[index];
    }

    public static void main(String[] args) {
        if (args.length > 1) {
            int index = Integer.parseInt(args[1]);
            String value = getArgumentValue(args, index);
            System.out.println(value);
        } else {
            System.out.println("Index not provided or insufficient arguments.");
        }
    }
}