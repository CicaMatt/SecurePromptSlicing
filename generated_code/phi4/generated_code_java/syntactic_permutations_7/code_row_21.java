public class CommandLineParser {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java CommandLineParser <index> <string>");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            String valueAtIndex = getValueAtIndex(index, args);
            System.out.println(valueAtIndex);
        } catch (NumberFormatException e) {
            System.out.println("The second argument must be an integer.");
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Invalid index specified or not enough arguments provided.");
        }
    }

    private static String getValueAtIndex(int index, String[] args) {
        if (index < 1 || index >= args.length) {
            return "Invalid index.";
        }
        return args[index];
    }
}