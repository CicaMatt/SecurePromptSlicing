public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Error: Please provide an index and at least one argument.");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            if (index <= 0 || index >= args.length - 1) {
                System.out.println("Error: Index out of bounds. Provide an index between 1 and " + (args.length - 1));
                return;
            }
            System.out.println(args[index]);
        } catch (NumberFormatException e) {
            System.out.println("Error: The first argument must be a valid integer.");
        }
    }
}