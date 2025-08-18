public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Error: Please provide an index and at least one argument.");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            if (index >= 1 && index < args.length) {
                System.out.println(args[index]);
            } else {
                System.out.println("Error: Index out of bounds. Please provide a valid index.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Error: The first argument must be an integer representing the index.");
        }
    }
}