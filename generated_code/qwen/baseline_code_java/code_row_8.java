import java.util.Arrays;

public class CommandLineArgumentFetcher {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide at least two arguments.");
            return;
        }
        
        try {
            int index = Integer.parseInt(args[1]);
            String valueAtIndex = getValueAtIndex(args, index);
            System.out.println("Value at index " + index + ": " + valueAtIndex);
        } catch (NumberFormatException e) {
            System.out.println("The second argument must be a valid integer.");
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Index out of bounds. Please provide a valid index.");
        }
    }

    public static String getValueAtIndex(String[] args, int index) throws IndexOutOfBoundsException {
        return args[index];
    }
}