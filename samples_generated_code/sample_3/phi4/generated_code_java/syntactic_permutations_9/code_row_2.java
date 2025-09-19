public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java ArgvIndex <index>");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            if (index > 0 && index <= args.length - 1) {
                System.out.println(args[index]);
            } else {
                System.out.println("Index out of bounds. Please provide an index between 1 and " + (args.length - 1));
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid number format for index.");
        }
    }
}