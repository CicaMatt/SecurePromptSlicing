public class CommandLineArgument {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }
        
        String argument = args[0];
        System.out.println("The provided argument is: " + argument);
    }
}