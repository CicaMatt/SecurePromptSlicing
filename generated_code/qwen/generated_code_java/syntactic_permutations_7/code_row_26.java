import java.util.Scanner;

public class CommandLineArgumentPrinter {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide at least two command line arguments.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            if (index >= args.length || index < 0) {
                System.out.println("Index is out of bounds.");
            } else {
                System.out.println(args[index]);
            }
        } catch (NumberFormatException e) {
            System.out.println("The second argument must be an integer.");
        }
    }
}