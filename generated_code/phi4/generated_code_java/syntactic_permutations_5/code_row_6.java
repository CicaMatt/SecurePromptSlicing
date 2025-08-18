import java.util.Scanner;

public class CommandLineIndex {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one command line argument.");
            return;
        }

        int index;
        try {
            index = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("The provided argument is not a valid integer.");
            return;
        }

        String[] elements = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};

        if (index < 0 || index >= elements.length) {
            System.out.println("Index out of bounds. Please provide an index between 0 and " + (elements.length - 1) + ".");
        } else {
            System.out.println("Element at index " + index + ": " + elements[index]);
        }
    }
}