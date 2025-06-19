import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("You must provide exactly one command-line argument.");
            return;
        }

        String arg = args[0].trim();

        System.out.println(arg);
    }
}