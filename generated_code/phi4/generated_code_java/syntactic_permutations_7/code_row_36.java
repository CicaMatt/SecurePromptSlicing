import java.util.Optional;

public class CommandLineStringToInt {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Not enough arguments.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            Optional<String> stringAtIndex = getArgumentAtIndex(index, args);

            stringAtIndex.ifPresentOrElse(
                s -> printString(s),
                () -> System.out.println("Invalid index or not enough command line arguments.")
            );
        } catch (NumberFormatException e) {
            System.out.println("Second argument must be an integer.");
        }
    }

    private static Optional<String> getArgumentAtIndex(int index, String[] args) {
        if (index >= 0 && index < args.length) {
            return Optional.ofNullable(args[index]);
        }
        return Optional.empty();
    }

    private static void printString(String s) {
        System.out.println(s);
    }
}