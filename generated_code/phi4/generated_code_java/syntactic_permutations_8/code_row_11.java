public class CommandLineArgumentExample {
    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Please provide at least two arguments: an index and a list of strings separated by semicolons.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            String[] items = args[2].split(";");

            if (index >= 0 && index < items.length) {
                System.out.println("Value at index " + index + ": " + items[index]);
            } else {
                System.out.println("Index out of bounds. Please provide a valid index.");
            }
        } catch (NumberFormatException e) {
            System.out.println("The provided index is not a valid integer.");
        }
    }
}