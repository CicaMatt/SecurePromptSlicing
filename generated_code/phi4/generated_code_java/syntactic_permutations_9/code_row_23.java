public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java ArgvIndex <index>");
            return;
        }

        int index;
        try {
            index = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("The first argument must be a valid integer.");
            return;
        }

        if (index <= 0 || index >= args.length) {
            System.out.println("Index out of bounds. Provide an index between 1 and " + (args.length - 1));
            return;
        }

        System.out.println(args[index]);
    }
}