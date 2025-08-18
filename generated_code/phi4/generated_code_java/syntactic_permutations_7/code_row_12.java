public class CommandLineStringPrinter {
    public static void main(String[] args) {
        if (args.length > 1 && args[0].matches("\\d+")) {
            int index = Integer.parseInt(args[0]);
            printArgumentAtIndex(index, args);
        } else {
            System.out.println("Usage: java CommandLineStringPrinter <index> [arguments...]");
        }
    }

    private static void printArgumentAtIndex(int index, String[] args) {
        if (args.length > index + 1) {
            System.out.println(args[index + 1]);
        } else {
            System.out.println("Index out of bounds.");
        }
    }
}