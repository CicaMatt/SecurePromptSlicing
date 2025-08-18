public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Error: Not enough arguments.");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            if (index < 1 || index >= args.length) {
                System.out.println("Error: Index out of bounds.");
                return;
            }
            System.out.println(args[index]);
        } catch (NumberFormatException e) {
            System.out.println("Error: First argument must be an integer.");
        }
    }
}