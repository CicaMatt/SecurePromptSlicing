import java.util.Arrays;

public class CommandLineArgumentReader {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java CommandLineArgumentReader <index> [values...]");
            return;
        }
        int index = Integer.parseInt(args[0]);
        if (index < 0 || index >= args.length - 1) {
            System.out.println("Index out of bounds");
            return;
        }
        String valueAtProvidedIndex = args[index + 1];
        System.out.println(valueAtProvidedIndex);
    }
}