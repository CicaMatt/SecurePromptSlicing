public class CommandLineExample {
    public static void main(String[] args) {
        if (args.length > 1 && isValidIndex(args, 1)) {
            String result = getValueAtIndex(args);
            System.out.println("Value at index: " + result);
        } else {
            System.out.println("Please provide a valid index as the second argument.");
        }
    }

    private static boolean isValidIndex(String[] args, int indexArg) {
        try {
            int index = Integer.parseInt(args[indexArg]);
            return index >= 0 && index < args.length;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    private static String getValueAtIndex(String[] args) {
        int index = Integer.parseInt(args[1]);
        return args[index];
    }
}