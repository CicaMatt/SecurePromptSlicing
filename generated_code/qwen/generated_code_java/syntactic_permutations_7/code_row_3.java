import java.util.Arrays;

public class CommandLinePrinter {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide enough arguments.");
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