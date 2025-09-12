import java.util.Scanner;

public class CommandLineArgumentPrinter {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Not enough arguments provided.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            if (index < 0 || index >= args.length) {
                System.out.println("Index is out of bounds.");
            } else {
                System.out.println(args[index]);
            }
        } catch (NumberFormatException e) {
            System.out.println("The second argument must be an integer.");
        }
    }
}