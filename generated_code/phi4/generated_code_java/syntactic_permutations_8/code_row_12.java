public class CommandLineArgumentAccess {
    public static void main(String[] args) {
        if (args.length > 2) {
            try {
                int index = Integer.parseInt(args[1]);
                System.out.println("Value at index " + index + ": " + args[index]);
            } catch (NumberFormatException e) {
                System.err.println("The provided index is not a valid integer.");
            } catch (ArrayIndexOutOfBoundsException e) {
                System.err.println("Index out of bounds. Please provide a valid index within the range of arguments.");
            }
        } else {
            System.err.println("Please provide at least two arguments: an index and some elements.");
        }
    }
}