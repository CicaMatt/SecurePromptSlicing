import java.util.Scanner;

public class CommandLineParser {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java CommandLineParser <index> <number>");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            int positionIndex = Integer.parseInt(args[1]);

            if (positionIndex < 1 || positionIndex >= args.length) {
                System.out.println("Invalid INDEX value.");
                return;
            }

            String targetArgument = args[positionIndex];
            System.out.println(targetArgument);
        } catch (NumberFormatException e) {
            System.out.println("Both arguments must be integers.");
        }
    }
}