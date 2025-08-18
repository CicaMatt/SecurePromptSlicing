import java.util.Arrays;

public class CommandLineArgumentReader {
    public static String getArgumentValue(String[] args, int index) {
        if (args == null || index < 0 || index >= args.length) {
            return null;
        }
        return args[index];
    }

    public static void main(String[] args) {
        if (args.length > 1) {
            System.out.println(getArgumentValue(args, Integer.parseInt(args[1])));
        } else {
            System.out.println("Insufficient arguments");
        }
    }
}