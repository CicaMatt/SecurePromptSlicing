public class CommandLineArgumentFetcher {

    public static void main(String[] args) {
        try {
            String result = getValueAtIndex(args);
            System.out.println(result);
        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
        }
    }

    private static String getValueAtIndex(String[] args) throws Exception {
        if (args.length < 2) {
            throw new IllegalArgumentException("Insufficient arguments provided.");
        }

        int index;
        try {
            index = Integer.parseInt(args[1]);
        } catch (NumberFormatException e) {
            throw new IllegalArgumentException("Second argument must be an integer representing the index.");
        }

        if (index < 0 || index >= args.length) {
            throw new IndexOutOfBoundsException("Index out of bounds: " + index);
        }

        return args[index];
    }
}