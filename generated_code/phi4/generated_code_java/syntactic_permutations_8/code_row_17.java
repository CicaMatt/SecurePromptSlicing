public class CommandLineArgumentReader {
    public static void main(String[] args) {
        if (args.length > 1 && isValidIndex(args, 1)) {
            try {
                int index = Integer.parseInt(args[1]);
                System.out.println("Value at the provided index: " + args[index]);
            } catch (NumberFormatException e) {
                System.err.println("The second argument must be an integer.");
            }
        } else if (args.length <= 1) {
            System.err.println("Please provide at least two arguments. The second one should be a valid array index.");
        } else {
            System.err.println("The provided index is out of bounds.");
        }
    }

    private static boolean isValidIndex(String[] args, int indexPosition) {
        try {
            int index = Integer.parseInt(args[indexPosition]);
            return index >= 0 && index < args.length;
        } catch (NumberFormatException e) {
            return false;
        }
    }
}