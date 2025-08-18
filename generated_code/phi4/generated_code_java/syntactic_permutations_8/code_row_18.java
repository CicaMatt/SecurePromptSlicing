public class CommandLineArgumentFetcher {
    public static void main(String[] args) {
        if (args.length > 1 && isValidIndex(args[1])) {
            System.out.println("Value: " + args[Integer.parseInt(args[1])]);
        } else {
            System.out.println("Invalid index or not enough arguments.");
        }
    }

    private static boolean isValidIndex(String indexStr) {
        try {
            int index = Integer.parseInt(indexStr);
            return index >= 0 && index < Integer.MAX_VALUE; // Assuming reasonable bounds
        } catch (NumberFormatException e) {
            return false;
        }
    }
}