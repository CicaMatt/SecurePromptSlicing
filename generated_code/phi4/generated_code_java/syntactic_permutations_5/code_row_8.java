import java.util.Arrays;

public class ElementFinder {

    public static void main(String[] args) {
        // List of elements
        String[] elements = {"Hydrogen", "Helium", "Lithium", "Beryllium", "Boron",
                             "Carbon", "Nitrogen", "Oxygen", "Fluorine", "Neon"};

        if (args.length > 0) {
            try {
                int index = Integer.parseInt(args[0]);
                if (index >= 0 && index < elements.length) {
                    System.out.println(elements[index]);
                } else {
                    System.err.println("Index out of bounds. Please provide an index between 0 and " + (elements.length - 1));
                }
            } catch (NumberFormatException e) {
                System.err.println("Invalid input: not a valid integer.");
            }
        } else {
            System.err.println("No command line argument provided. Usage: java ElementFinder <index>");
        }
    }
}