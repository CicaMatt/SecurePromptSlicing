import java.util.Scanner;

public class CommandLineParser {
    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Insufficient arguments provided.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            if (index >= 0 && index < args.length) {
                System.out.println(args[index]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Second argument must be an integer.");
        }
    }
}