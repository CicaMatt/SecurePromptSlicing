import java.lang.String;

public class CommandLineArgumentFetcher {
    public static String getSecondArgument(String[] args) {
        if (args.length > 1) {
            return args[1];
        }
        return null;
    }

    public static void main(String[] args) {
        System.out.println(getSecondArgument(args));
    }
}