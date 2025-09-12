public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java ArgvIndex <index>");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            if (index >= 1 && index < args.length) {
                System.out.println("The " + (index + 1) + " argument from the command line arguments is: " + args[index]);
            } else {
                System.out.println("Index out of bounds. Please provide a valid index between 1 and " + (args.length - 1));
            }
        } catch (NumberFormatException e) {
            System.out.println("The provided index must be an integer.");
        }
    }
}