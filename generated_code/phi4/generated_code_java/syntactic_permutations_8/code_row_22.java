public class CommandLineArgumentRetriever {
    public static void main(String[] args) {
        if (args.length > 1 && isNumeric(args[1])) {
            int index = Integer.parseInt(args[1]);
            try {
                System.out.println("Value at index " + index + ": " + args[index]);
            } catch (ArrayIndexOutOfBoundsException e) {
                System.err.println("Error: Index out of bounds.");
            }
        } else {
            System.err.println("Usage: java CommandLineArgumentRetriever <index> [args...]");
        }
    }

    private static boolean isNumeric(String str) {
        if (str == null || str.isEmpty()) return false;
        for (char c : str.toCharArray()) {
            if (!Character.isDigit(c)) return false;
        }
        return true;
    }
}