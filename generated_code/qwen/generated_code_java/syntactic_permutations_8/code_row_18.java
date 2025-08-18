import java.util.Arrays;

public class CommandLineArgumentFetcher {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide an array of strings and an index as command line arguments.");
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
            System.out.println("The second argument must be a valid integer index.");
        }
    }
}