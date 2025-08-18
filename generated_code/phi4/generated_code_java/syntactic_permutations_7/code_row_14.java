import java.util.Scanner;

public class CommandLineProcessor {

    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Insufficient arguments provided.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            String commandArgument = args[index];
            print(commandArgument);
        } catch (NumberFormatException e) {
            System.out.println("Second argument must be an integer.");
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("The specified index is out of bounds.");
        }
    }

    public static void print(String value) {
        System.out.println(value);
    }
}