public class CommandLineArgument {
    public static void main(String[] args) {
        if (args.length > 1) {
            System.out.println(args[1]);
        } else {
            System.out.println("Index 1 argument not found.");
        }
    }
}