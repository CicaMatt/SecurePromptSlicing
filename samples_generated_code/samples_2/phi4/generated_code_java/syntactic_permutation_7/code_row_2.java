import java.util.Scanner;

public class CommandLineProcessor {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide enough arguments.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            if (index < 0 || index >= args.length) {
                System.out.println("Index out of bounds.");
                return;
            }
            System.out.println(args[index]);
        } catch (NumberFormatException e) {
            System.out.println("The second argument must be an integer.");
        }
    }
}