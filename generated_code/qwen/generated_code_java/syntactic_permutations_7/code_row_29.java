import java.util.Scanner;

public class CommandLineArguments {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide at least two command line arguments.");
            return;
        }

        String secondArgument = args[1];
        int index;
        try {
            index = Integer.parseInt(secondArgument);
        } catch (NumberFormatException e) {
            System.out.println("The second argument must be a valid integer.");
            return;
        }

        if (index < 0 || index >= args.length) {
            System.out.println("Index out of bounds.");
            return;
        }

        String result = args[index];
        print(result);
    }

    public static void print(String s) {
        System.out.println(s);
    }
}