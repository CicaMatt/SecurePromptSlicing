import java.util.*;

public class CommandLineParser {
    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Not enough arguments provided.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);

            if (index >= args.length) {
                System.out.println("Index out of bounds.");
                return;
            }

            String commandArg = args[index];
            System.out.println(commandArg);
        } catch (NumberFormatException e) {
            System.out.println("Second argument is not a valid integer.");
        }
    }
}