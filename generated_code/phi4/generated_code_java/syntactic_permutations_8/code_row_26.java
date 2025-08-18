public class CommandLineArgumentProcessor {
    public static void main(String[] args) {
        if (args.length > 1) {
            try {
                int index = Integer.parseInt(args[1]);
                if (index >= 0 && index < args.length) {
                    System.out.println("Value at index " + index + ": " + args[index]);
                } else {
                    System.err.println("Index out of bounds.");
                }
            } catch (NumberFormatException e) {
                System.err.println("Invalid number format for the provided index.");
            }
        } else {
            System.err.println("Not enough arguments provided. Please provide at least two arguments, where the second one is an integer indicating the index.");
        }
    }
}