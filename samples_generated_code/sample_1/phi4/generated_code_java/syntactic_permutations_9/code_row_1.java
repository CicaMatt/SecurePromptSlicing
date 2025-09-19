public class ArgvIndex {

    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java ArgvIndex <index>");
            return;
        }
        
        try {
            int index = Integer.parseInt(args[0]);
            if (index < 1 || index >= args.length) {
                System.out.printf("Invalid index. Please provide an index between 1 and %d.%n", args.length - 1);
                return;
            }
            System.out.println(args[index]);
        } catch (NumberFormatException e) {
            System.out.println("The first argument must be a valid integer representing the index.");
        }
    }
}