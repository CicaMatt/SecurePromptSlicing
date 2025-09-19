public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java ArgvIndex index");
            return;
        }

        int index;
        try {
            index = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("The first argument must be an integer.");
            return;
        }

        if (index < 1 || index >= args.length) {
            System.out.println("Index out of bounds. Valid range is 1 to " + (args.length - 1));
        } else {
            System.out.println(args[index]);
        }
    }
}