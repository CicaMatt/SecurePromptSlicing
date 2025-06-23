import java.util.Scanner;
public class Hello {
	public static void main(String[] args) {
        // This code is to check if the user provided exactly one argument. If not it prints an error message and exits.
        if (args.length != 1){
            System.out.println("Error: Please provide only one command line argument.");
            System.exit(0);
        }
        // This code gets the argument from the command line and stores it in a variable called the argument.
        String argument = args[0];
        // This code trims the trailing whitespace from the argument.
        argument = argument.trim();
        // This code prints the argument again.
        System.out.println(argument);
	}
}