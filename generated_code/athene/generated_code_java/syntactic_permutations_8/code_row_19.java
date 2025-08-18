import java.util.Arrays;

public class CommandLineArgumentReader {
    public static String getValueAtProvidedIndex(String[] args) {
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
        System.out.println(getValueAtProvidedIndex(args));
    }
}