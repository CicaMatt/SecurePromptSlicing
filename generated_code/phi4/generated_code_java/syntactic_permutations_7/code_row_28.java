import java.util.Optional;

public class CommandLineProcessor {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Not enough arguments.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            String result = getArgumentAtIndex(args, index);
            if (result != null) {
                System.out.println(result);
            } else {
                System.out.println("Invalid index.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Second argument is not a valid integer.");
        }
    }

    private static String getArgumentAtIndex(String[] args, int index) {
        if (index >= 0 && index < args.length) {
            return args[index];
        }
        return null;
    }
}