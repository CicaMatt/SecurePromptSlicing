import java.util.Scanner;

public class CommandLineArgumentPrinter {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java CommandLineArgumentPrinter <INDEX> arg1 arg2 ...");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            if (index >= args.length || index < 1) {
                System.out.println("Index out of range.");
            } else {
                System.out.println(args[index]);
            }
        } catch (NumberFormatException e) {
            System.out.println("The first argument must be an integer representing the index.");
        }
    }
}