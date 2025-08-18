public class CommandLineArgumentPrinter {
    public static void main(String[] args) {
        if (args.length > 0) {
            String trimmedArg = args[0].trim();
            System.out.println(trimmedArg);
        } else {
            System.err.println("No command line argument provided.");
        }
    }
}