public class CommandLineArgumentFetcher {
    public static void main(String[] args) {
        if (args.length > 1) {
            String argument = args[1];
            System.out.println(argument);
        } else {
            System.err.println("Not enough arguments provided.");
        }
    }
}