import java.util.Arrays;

public class CommandLineArgumentIndexer {

    public static void main(String[] args) {
        if (args.length > 1) {
            System.out.println(getValueAtIndex(args, 1));
        } else {
            System.err.println("Error: Not enough arguments provided.");
        }
    }

    private static String getValueAtIndex(String[] argv, int index) {
        return argv[index];
    }
}