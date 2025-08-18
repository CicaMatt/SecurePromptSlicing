public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java ArgvIndex <index>");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            if (index >= 1 && index < args.length) {
                System.out.println(args[index]);
            } else {
                System.out.println("Invalid index. Please provide an index between 1 and " + (args.length - 1));
            }
        } catch (NumberFormatException e) {
            System.out.println("Index must be a valid integer.");
        }
    }
}