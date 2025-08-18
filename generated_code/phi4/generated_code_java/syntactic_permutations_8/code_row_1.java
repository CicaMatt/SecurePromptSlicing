public class CommandLineIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Not enough arguments. Please provide an index.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            if (index < 0 || index >= args.length) {
                System.out.println("Index out of bounds.");
            } else {
                System.out.println("Value at the provided index: " + args[index]);
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid number format for index.");
        }
    }
}