public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide an index and at least one argument.");
            return;
        }

        int index;
        
        try {
            index = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("The first argument must be a valid integer representing the index.");
            return;
        }
        
        if (index < 1 || index >= args.length) {
            System.out.printf("Index %d is out of bounds. Please provide an index between 1 and %d.\n", index, args.length - 1);
        } else {
            System.out.println(args[index]);
        }
    }
}