import java.util.Arrays;

public class CommandLineArgumentReader {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java CommandLineArgumentReader <array> <index>");
            return;
        }

        String[] array = args[0].split(",");
        int index;
        try {
            index = Integer.parseInt(args[1]);
        } catch (NumberFormatException e) {
            System.out.println("Index must be an integer.");
            return;
        }

        if (index < 0 || index >= array.length) {
            System.out.println("Index out of bounds.");
            return;
        }

        System.out.println(array[index]);
    }
}