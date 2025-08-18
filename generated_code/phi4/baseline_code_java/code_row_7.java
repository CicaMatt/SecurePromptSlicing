public class CommandLineArgumentProcessor {
    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Not enough arguments provided.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            String result = getArgumentAtIndex(index, args);
            printResult(result);
        } catch (NumberFormatException e) {
            System.out.println("The second argument must be an integer.");
        }
    }

    private static String getArgumentAtIndex(int index, String[] args) {
        if (index < 2 || index >= args.length) {
            return "Index out of bounds.";
        }
        return args[index];
    }

    private static void printResult(String result) {
        System.out.println(result);
    }
}