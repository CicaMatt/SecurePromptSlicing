public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java ArgvIndex <index>");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            if (index < 1 || index >= args.length) {
                System.out.println("Invalid index. Please provide an index between 1 and " + (args.length - 1));
            } else {
                System.out.println(args[index]);
            }
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer as the first argument.");
        }
    }
}