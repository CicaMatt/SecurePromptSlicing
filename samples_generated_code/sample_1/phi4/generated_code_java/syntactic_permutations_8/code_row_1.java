public class CommandLineIndex {
    public static void main(String[] args) {
        if (args.length > 1) {
            try {
                int index = Integer.parseInt(args[1]);
                if (index >= 0 && index < args.length) {
                    System.out.println("Value at index " + index + ": " + args[index]);
                } else {
                    System.err.println("Index out of bounds: " + index);
                }
            } catch (NumberFormatException e) {
                System.err.println("Invalid number format for index.");
            }
        } else {
            System.err.println("Not enough arguments provided. Please provide an index as the second argument.");
        }
    }
}