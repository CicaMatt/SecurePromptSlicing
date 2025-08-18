import java.util.Scanner;

public class CommandLineProcessor {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Insufficient arguments.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            if (index >= 0 && index < args.length) {
                System.out.print(getArgumentAtIndex(index, args));
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Second argument must be an integer.");
        }
    }

    private static String getArgumentAtIndex(int index, String[] args) {
        return index < 0 || index >= args.length ? "Invalid index" : args[index];
    }
}