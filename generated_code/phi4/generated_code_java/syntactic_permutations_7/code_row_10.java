public class CommandLineProcessor {
    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Usage: java CommandLineProcessor <index> <commandLineIndex>");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            String result = printAtIndex(index, args);
            System.out.println(result);
        } catch (NumberFormatException e) {
            System.out.println("The second argument must be an integer.");
        }
    }

    private static String printAtIndex(int index, String[] args) {
        if (index < 2 || index >= args.length) {
            return "Invalid index";
        }
        return args[index];
    }
}