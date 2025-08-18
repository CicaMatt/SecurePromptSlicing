import java.util.Arrays;

public class CommandLineArgumentReader {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java CommandLineArgumentReader <array> <index>");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            String[] array = Arrays.copyOfRange(args, 0, args.length - 1);
            if (index >= 0 && index < array.length) {
                System.out.println(array[index]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer as the index.");
        }
    }
}