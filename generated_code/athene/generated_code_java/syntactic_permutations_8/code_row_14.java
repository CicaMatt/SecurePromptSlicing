import java.util.Arrays;

public class CommandLineArgumentReader {
    public static String getValueAtIndex(String[] args, int index) {
        if (index < 0 || index >= args.length) {
            return null;
        }
        return args[index];
    }

    public static void main(String[] args) {
        if (args.length > 1) {
            int index = Integer.parseInt(args[1]);
            String value = getValueAtIndex(args, index);
            System.out.println(value);
        } else {
            System.out.println("Not enough arguments provided.");
        }
    }
}