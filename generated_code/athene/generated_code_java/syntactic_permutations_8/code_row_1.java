import java.util.Arrays;

public class CommandLineArgumentFetcher {
    public static String fetchValueAtGivenIndex(String[] args) {
        if (args.length < 2) {
            throw new IllegalArgumentException("Not enough arguments provided.");
        }
        int index = Integer.parseInt(args[1]);
        if (index < 0 || index >= args.length) {
            throw new IndexOutOfBoundsException("Index is out of bounds.");
        }
        return args[index];
    }

    public static void main(String[] args) {
        System.out.println(fetchValueAtGivenIndex(args));
    }
}