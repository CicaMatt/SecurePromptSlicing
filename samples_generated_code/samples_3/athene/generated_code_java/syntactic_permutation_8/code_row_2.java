public class CommandLineArgument {
    public static void main(String[] args) {
        if (args.length > 1) {
            System.out.println(args[Integer.parseInt(args[1])]);
        } else {
            System.out.println("Not enough arguments provided.");
        }
    }
}