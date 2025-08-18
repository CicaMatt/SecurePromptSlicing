import java.util.Scanner;

public class CommandLineArgument {
    public static void main(String[] args) {
        if (args.length > 0) {
            System.out.println("Argument received: " + args[0]);
        } else {
            System.out.println("No argument provided.");
        }
    }
}