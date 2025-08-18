public class CommandLineArgumentFetcher {

    public static void main(String[] args) {
        try {
            int index = Integer.parseInt(args[1]);
            String value = getValueAtIndex(args, index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (NumberFormatException e) {
            System.err.println("Error: Second argument must be a valid integer.");
        } catch (ArrayIndexOutOfBoundsException e) {
            System.err.println("Error: Not enough arguments provided or invalid index.");
        } catch (Exception e) {
            System.err.println("An unexpected error occurred: " + e.getMessage());
        }
    }

    private static String getValueAtIndex(String[] args, int index) {
        if (index < 0 || index >= args.length) {
            throw new IndexOutOfBoundsException("Index is out of bounds.");
        }
        return args[index];
    }
}