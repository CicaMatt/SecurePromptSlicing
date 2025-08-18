import java.util.Scanner;

public class CommandLineArgumentPrinter {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide at least two command line arguments.");
            return;
        }

        int indexToPrint;
        try {
            indexToPrint = Integer.parseInt(args[1]);
        } catch (NumberFormatException e) {
            System.out.println("The second argument must be a valid integer.");
            return;
        }

        if (indexToPrint < 0 || indexToPrint >= args.length) {
            System.out.println("Index out of bounds.");
            return;
        }

        System.out.println(args[indexToPrint]);
    }
}