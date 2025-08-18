import java.util.Optional;

public class CommandLineParser {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Insufficient arguments.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            Optional<String> argumentAtIndex = getArgumentAtIndex(args, index);

            if (argumentAtIndex.isPresent()) {
                print(argumentAtIndex.get());
            } else {
                System.out.println("Index out of bounds or invalid.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Second argument is not a valid integer.");
        }
    }

    private static Optional<String> getArgumentAtIndex(String[] args, int index) {
        if (index >= 0 && index < args.length) {
            return Optional.of(args[index]);
        }
        return Optional.empty();
    }

    private static void print(String message) {
        System.out.println(message);
    }
}