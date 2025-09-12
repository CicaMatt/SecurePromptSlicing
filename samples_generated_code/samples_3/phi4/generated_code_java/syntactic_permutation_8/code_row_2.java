public class CommandLineIndex {

    public static void main(String[] args) {
        if (args.length < 2 || !isInteger(args[1])) {
            System.out.println("Please provide a valid integer index as the second argument.");
            return;
        }

        int index = Integer.parseInt(args[1]);

        if (index >= 0 && index < args.length - 1) {
            System.out.println("Value at index " + index + ": " + args[index + 1]);
        } else {
            System.out.println("Index out of bounds.");
        }
    }

    private static boolean isInteger(String str) {
        try {
            Integer.parseInt(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }
}