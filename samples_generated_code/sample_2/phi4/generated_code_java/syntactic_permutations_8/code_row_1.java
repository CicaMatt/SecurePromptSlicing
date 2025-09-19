public class CommandLineExample {
    public static void main(String[] args) {
        if (args.length < 2 || !isPositiveInteger(args[1])) {
            System.out.println("Please provide a valid positive integer as the second argument.");
            return;
        }

        int index = Integer.parseInt(args[1]);
        if (index >= args.length) {
            System.out.println("Index out of bounds. Please ensure the provided index is within range.");
        } else {
            System.out.println("Value at index " + index + ": " + args[index]);
        }
    }

    private static boolean isPositiveInteger(String str) {
        try {
            int value = Integer.parseInt(str);
            return value > 0;
        } catch (NumberFormatException e) {
            return false;
        }
    }
}