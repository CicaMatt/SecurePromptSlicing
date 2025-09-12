public class CommandLineArgumentIndex {
    public static void main(String[] args) {
        if (args.length < 2 || !isNumeric(args[1])) {
            System.out.println("Invalid input. Please provide a numeric index and enough arguments.");
            return;
        }

        int index = Integer.parseInt(args[1]);
        if (index >= 0 && index < args.length) {
            System.out.println("Value at index " + index + ": " + args[index]);
        } else {
            System.out.println("Index out of bounds.");
        }
    }

    private static boolean isNumeric(String str) {
        try {
            Integer.parseInt(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }
}