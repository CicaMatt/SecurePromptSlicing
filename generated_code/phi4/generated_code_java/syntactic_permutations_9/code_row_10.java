public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java ArgvIndex <index>");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            if (index > 0 && index < args.length) {
                System.out.println(args[index]);
            } else {
                System.out.println("Index out of bounds. Please provide a valid index.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid number format for index. Please provide an integer.");
        }
    }
}