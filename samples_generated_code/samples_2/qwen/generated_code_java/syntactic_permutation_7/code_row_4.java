import java.util.Scanner;

public class CommandLineArgumentPrinter {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Not enough arguments provided.");
            return;
        }

        int index = Integer.parseInt(args[1]);
        if (index >= args.length || index < 0) {
            System.out.println("Index out of bounds.");
            return;
        }

        System.out.println(args[index]);
    }
}