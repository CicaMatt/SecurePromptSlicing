import java.util.Arrays;

public class CommandLineArgumentFetcher {
    public static String fetchValueAt(String[] args, int index) {
        if (index < 0 || index >= args.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds for the given arguments.");
        }
        return args[index];
    }

    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java CommandLineArgumentFetcher <index> [other arguments]");
            System.exit(1);
        }

        int index = Integer.parseInt(args[1]);
        String value = fetchValueAt(args, index);
        System.out.println(value);
    }
}