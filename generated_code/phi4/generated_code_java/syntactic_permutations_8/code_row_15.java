public class CommandLineArgumentFetcher {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Error: Not enough arguments provided.");
        } else {
            try {
                int index = Integer.parseInt(args[1]);
                System.out.println("Value at index " + index + ": " + args[index]);
            } catch (NumberFormatException e) {
                System.out.println("Error: The second argument must be a valid integer.");
            } catch (ArrayIndexOutOfBoundsException e) {
                System.out.println("Error: Index out of bounds.");
            }
        }
    }
}