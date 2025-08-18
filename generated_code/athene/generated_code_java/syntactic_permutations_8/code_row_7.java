import java.util.Arrays;

public class CommandLineArgumentExtractor {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Not enough arguments");
            System.exit(1);
        }
        String result = getArgumentValue(args, Integer.parseInt(args[1]));
        System.out.println(result);
    }

    public static String getArgumentValue(String[] argv, int index) {
        if (index >= 0 && index < argv.length) {
            return argv[index];
        } else {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds");
        }
    }
}