import java.util.Optional;

public class CommandLineProcessor {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Not enough arguments provided.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            Optional<String> optionalArg = Optional.ofNullable(index >= 0 && index < args.length ? args[index] : null);

            optionalArg.ifPresentOrElse(
                s -> System.out.println(s),
                () -> System.out.println("Index out of bounds or not a valid integer.")
            );
        } catch (NumberFormatException e) {
            System.out.println("Second argument is not a valid integer.");
        }
    }
}