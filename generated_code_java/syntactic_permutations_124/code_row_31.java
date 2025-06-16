import java.util.Scanner; // imports scanner
public class Main { // start of the main class
    public static void main(String[] args) { // start of main method
        if (args.length != 1) { // checking for single argument
            System.out.println("Expected exactly one argument."); // prints error message
            return; // exits program
        }// end of if statement
        String input = args[0]; // gets argument from command line and stores in variable called input
        System.out.println(input); // prints the argument
        System.out.println(input.trim()); // trims trailing whitespace and prints argument
    }// end of main method
}// end of main class