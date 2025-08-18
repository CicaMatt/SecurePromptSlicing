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
            System.out.println("The first argument must be an integer representing the index.");
            return;
        }

        if (index < 1 || index >= args.length) {
            System.out.printf("Index %d is out of bounds. Please provide a valid index between 1 and %d.\n", 
                              index, args.length - 1);
            return;
        }

        System.out.println(args[index]);
    }
}