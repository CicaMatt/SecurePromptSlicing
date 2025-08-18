public class CommandLineArgumentPrinter {
    public static void main(String[] args) {
        if (args.length < 2 || !isNumeric(args[1])) {
            System.out.println("Usage: java CommandLineArgumentPrinter <index> <arguments...>");
            return;
        }
        
        int index = Integer.parseInt(args[1]);
        printArgumentAtIndex(index, args);
    }

    private static void printArgumentAtIndex(int index, String[] args) {
        if (args.length <= index + 1) { // Account for the shift by first argument being program name
            System.out.println("Index out of bounds");
        } else {
            System.out.println(args[index + 1]);
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