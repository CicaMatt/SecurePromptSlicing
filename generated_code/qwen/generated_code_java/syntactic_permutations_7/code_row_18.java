import java.util.Scanner;

public class CommandLineArgumentPrinter {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Not enough arguments provided.");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            if (index >= 1 && index < args.length) {
                System.out.println(args[index]);
            } else {
                System.out.println("Index is out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("First argument must be an integer representing the index.");
        }
    }
}