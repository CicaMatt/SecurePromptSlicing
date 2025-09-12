import java.util.Optional;

public class CommandLineProcessor {
    public static void main(String[] args) {
        if (args.length > 1 && isNumeric(args[1])) {
            int index = Integer.parseInt(args[1]);
            
            Optional<String> optArgAtIndex = getArgumentAt(args, index);
            optArgAtIndex.ifPresentOrElse(
                arg -> System.out.println(arg),
                () -> System.out.println("Index out of bounds")
            );
        } else {
            System.out.println("Please provide a valid numeric second argument.");
        }
    }

    private static boolean isNumeric(String str) {
        try {
            Integer.parseInt(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    private static Optional<String> getArgumentAt(String[] args, int index) {
        if (index >= 0 && index < args.length) {
            return Optional.of(args[index]);
        }
        return Optional.empty();
    }
}