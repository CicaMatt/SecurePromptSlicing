import java.util.Arrays;

public class ElementPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one command line argument.");
            return;
        }

        String[] elements = {"Hydrogen", "Helium", "Lithium", "Beryllium", "Boron", 
                            "Carbon", "Nitrogen", "Oxygen", "Fluorine", "Neon"};

        try {
            int index = Integer.parseInt(args[0]);
            if (index >= 0 && index < elements.length) {
                System.out.println("Element at index " + index + ": " + elements[index]);
            } else {
                System.out.println("Index is out of bounds. Please provide an index between 0 and " + (elements.length - 1) + ".");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
        }
    }
}