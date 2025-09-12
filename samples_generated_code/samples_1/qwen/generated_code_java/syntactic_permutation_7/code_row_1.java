import java.util.Scanner;

public class CommandLineArgumentPrinter {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide at least two command line arguments.");
            return;
        }

        int index;
        try {
            index = Integer.parseInt(args[1]);
        } catch (NumberFormatException e) {
            System.out.println("The second argument must be a valid integer.");
            return;
        }

        if (index < 0 || index >= args.length) {
            System.out.println("Index is out of bounds.");
            return;
        }

        System.out.println(args[index]);
    }
}