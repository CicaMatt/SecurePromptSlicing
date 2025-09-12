public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java ArgvIndex <index>");
            return;
        }

        int index = 0;
        try {
            index = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer as the first argument.");
            return;
        }

        if (index < 1 || index >= args.length - 1) {
            System.out.println("Index out of bounds. Please use an index between 1 and " + (args.length - 1));
            return;
        }

        System.out.println(args[index]);
    }
}