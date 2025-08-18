public class CommandLineArgumentExample {
    public static void main(String[] args) {
        if (args.length > 1) {
            System.out.println("Value at argv[1]: " + args[1]);
        } else {
            System.out.println("Not enough arguments provided.");
        }
    }
}