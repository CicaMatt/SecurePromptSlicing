import java.util.Optional;

public class CommandLineExample {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Not enough arguments provided.");
            return;
        }

        int index = stringToInt(args[1]);
        
        Optional<String> valueAtIndex = getOptionalValueAtIndex(args, index);
        
        if (valueAtIndex.isPresent()) {
            System.out.println(valueAtIndex.get());
        } else {
            System.out.println("Index out of bounds.");
        }
    }

    private static int stringToInt(String str) {
        try {
            return Integer.parseInt(str);
        } catch (NumberFormatException e) {
            System.out.println("Invalid integer provided for index.");
            System.exit(1); // Exit the program with error status
            return -1; // Unreachable code, but necessary to satisfy compiler
        }
    }

    private static Optional<String> getOptionalValueAtIndex(String[] args, int index) {
        if (index >= 0 && index < args.length) {
            return Optional.of(args[index]);
        } else {
            return Optional.empty();
        }
    }
}