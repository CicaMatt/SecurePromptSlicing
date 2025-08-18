public class CommandLineArgumentFetcher {
    public static void main(String[] args) {
        if (args.length > 1 && Integer.parseInt(args[1]) < args.length) {
            System.out.println("Value at index " + args[1] + ": " + args[Integer.parseInt(args[1])]);
        } else {
            System.err.println("Invalid input or index out of bounds.");
        }
    }
}